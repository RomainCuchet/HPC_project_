#define _POSIX_C_SOURCE 199309L

#include "header.h"

#include <errno.h>

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <omp.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

typedef struct s_bench_record {
    char	program[32];
    uint64_t exec_time_ns;
    long double sum_result;
    long long N;
    int		num_procs;
} bench_record;

static void usage_controller(void)
{
    fprintf(stderr, "Usage: benchmark <max_n> <n_increment> <csv_output>\n");
}

static void usage_worker(void)
{
    fprintf(stderr, "Usage: benchmark --mpi-worker <N>\n");
}

static long long parse_positive(const char *arg, const char *name)
{
    char *end = NULL;
    long long value = strtoll(arg, &end, 10);
    if (!arg || *arg == '\0' || *end != '\0' || value <= 0)
    {
        fprintf(stderr, "%s must be a positive integer (got '%s')\n", name, arg ? arg : "");
        exit(EXIT_FAILURE);
    }
    if (value > INT_MAX)
    {
        fprintf(stderr, "%s must be <= %d\n", name, INT_MAX);
        exit(EXIT_FAILURE);
    }
    return value;
}

static uint64_t now_ns(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
        return 0ULL;
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

static int detect_max_threads(void)
{
    const char *env = getenv("BENCH_MAX_THREADS");
    if (env && *env)
    {
        char *end = NULL;
        long val = strtol(env, &end, 10);
        if (end && *end == '\0' && val > 0)
            return (int)val;
    }
    int max_threads = omp_get_max_threads();
    if (max_threads < 1)
        max_threads = 1;
    return max_threads;
}

static int detect_max_mpi_procs(void)
{
    const char *env = getenv("BENCH_MAX_MPI_PROCS");
    if (env && *env)
    {
        char *end = NULL;
        long val = strtol(env, &end, 10);
        if (end && *end == '\0' && val > 0)
            return (int)val;
    }
    long cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpus < 1)
        cpus = 1;
    if (cpus > 64)
        cpus = 64;
    return (int)cpus;
}

static void csv_write_header(FILE *fp)
{
    fprintf(fp, "program_name,exec_time_ns,sum_result,N,num_procs\n");
}

static void csv_append(FILE *fp, const bench_record *rec)
{
    fprintf(fp, "%s,%" PRIu64 ",%.10Lf,%lld,%d\n",
        rec->program, rec->exec_time_ns, rec->sum_result, rec->N, rec->num_procs);
    fflush(fp);
}

static void record_and_write(FILE *fp, const char *program, uint64_t duration,
                  long double sum, long long N, int procs)
{
    bench_record rec;
    memset(&rec, 0, sizeof(rec));
    strncpy(rec.program, program, sizeof(rec.program) - 1);
    rec.exec_time_ns = duration;
    rec.sum_result = sum;
    rec.N = N;
    rec.num_procs = procs;
    csv_append(fp, &rec);
}

static int run_command_capture(const char *cmd, long double *sum_out, uint64_t *duration_ns)
{
    uint64_t start = now_ns();
    FILE *pipe = popen(cmd, "r");
    if (!pipe)
    {
        fprintf(stderr, "Failed to run '%s': %s\n", cmd, strerror(errno));
        return -1;
    }

    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), pipe))
    {
        fprintf(stderr, "No output captured from '%s'\n", cmd);
        pclose(pipe);
        return -1;
    }

    char *end = NULL;
    long double parsed = strtold(buffer, &end);
    if (end == buffer)
    {
        fprintf(stderr, "Unable to parse result from '%s'\n", cmd);
        pclose(pipe);
        return -1;
    }

    int status = pclose(pipe);
    uint64_t elapsed = now_ns() - start;
    if (duration_ns)
        *duration_ns = elapsed;
    if (status == -1 || !WIFEXITED(status) || WEXITSTATUS(status) != 0)
    {
        fprintf(stderr, "Command '%s' failed (status=%d)\n", cmd, status);
        return -1;
    }
    if (sum_out)
        *sum_out = parsed;
    return 0;
}

static int run_mpi_worker(long long N)
{
    MPI_Init(NULL, NULL);
    int rank = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float result = mpi_sum((size_t)N);
    if (rank == 0)
        printf("%.10f\n", result);

    MPI_Finalize();
    return EXIT_SUCCESS;
}

static int controller_main(long long max_n, long long step, const char *csv_path)
{
    FILE *csv = fopen(csv_path, "w");
    if (!csv)
    {
        fprintf(stderr, "Failed to open %s: %s\n", csv_path, strerror(errno));
        return EXIT_FAILURE;
    }
    csv_write_header(csv);

    int max_threads = detect_max_threads();
    int max_mpi = detect_max_mpi_procs();
    char cmd[256];

    for (long long N = 1; N <= max_n; N += step)
    {
        uint64_t start = now_ns();
        long double sum = sum_iteratif(1, (int)N);
        record_and_write(csv, "iterative", now_ns() - start, sum, N, 1);

        start = now_ns();
        sum = sum_formula((int)N);
        record_and_write(csv, "formula", now_ns() - start, sum, N, 1);

        for (int t = 1; t <= max_threads; ++t)
        {
            omp_set_num_threads(t);
            start = now_ns();
            sum = omp_sum(1, (int)N);
            record_and_write(csv, "omp", now_ns() - start, sum, N, t);
        }

        for (int p = 1; p <= max_mpi; ++p)
        {
            snprintf(cmd, sizeof(cmd),
                 "mpirun -np %d ./benchmark --mpi-worker %lld",
                 p, N);
            uint64_t duration = 0;
            long double mpi_result = 0.0L;
            if (run_command_capture(cmd, &mpi_result, &duration) != 0)
            {
                fprintf(stderr,
                     "MPI benchmark failed for N=%lld, procs=%d\n",
                     N, p);
                fclose(csv);
                return EXIT_FAILURE;
            }
            record_and_write(csv, "mpi_sum", duration, mpi_result, N, p);
            sched_yield();
        }
    }

    fclose(csv);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc >= 2 && strcmp(argv[1], "--mpi-worker") == 0)
    {
        if (argc != 3)
        {
            usage_worker();
            return EXIT_FAILURE;
        }
        long long N = parse_positive(argv[2], "N");
        return run_mpi_worker(N);
    }

    if (argc != 4)
    {
        usage_controller();
        return EXIT_FAILURE;
    }

    long long max_n = parse_positive(argv[1], "max_n");
    long long step = parse_positive(argv[2], "n_increment");
    return controller_main(max_n, step, argv[3]);
}

#include "header.h"

#include <string.h>

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

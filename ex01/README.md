# Benchmark Usage Guide

This project ships a single binary `benchmark` that measures the performance of three approaches to compute the partial harmonic series \(\sum_{i=1}^{N}\frac{1}{i(i+1)}\):

- **Iterative** (classic series) — runs `sum_iteratif` sequentially.
- **OpenMP** — uses `omp_sum` with a variable thread count.
- **MPI** — distributes the sum with `MPI_Allreduce`, now invoked for every available process count.
- **Formula** — applies the closed-form `sum_formula` for an O(1) reference.

## Prerequisites

- Linux (or equivalent POSIX system)
- MPI implementation providing `mpicc`
- GCC with OpenMP support

## Build

```bash
make
```

This command builds `benchmark`. Use `make clean` to remove objects and the executable.

## Run

Syntax:

```bash
./benchmark <max_n> <n_increment> <csv_output>
```

- `max_n`: maximum N value.
- `n_increment`: step between two N values.
- `csv_output`: CSV file (overwritten) receiving results.

The program autodetects the logical core count (`omp_get_max_threads`) for the OpenMP sweep. To restrict the tested thread counts, set `BENCH_MAX_THREADS` before running:

```bash
BENCH_MAX_THREADS=4 ./benchmark 1000 100 results.csv
```

The MPI variant is now executed once for each available number of processes discovered at runtime.

## CSV Format

Header:

```
program_name,exec_time_ns,sum_result,N,num_procs
```

Each line records a single run:

- `program_name`: `iterative`, `formula`, `omp`, `mpi`
- `exec_time_ns`: duration in nanoseconds (measured with `clock_gettime`)
- `sum_result`: returned numerical result
- `N`: current value
- `num_procs`: threads (OpenMP) or processes (MPI) used (1 for formula/iterative)

Sample output:

```
program_name,exec_time_ns,sum_result,N,num_procs
iterative,482,0.5000000000,1,1
formula,56,0.5000000000,1,1
omp,69444,0.5000000000,1,1
mpi,6129,0.5000000000,1,1
```

## Customization

- **Measurement density**: tune `n_increment` to densify or thin the sweep.
- **Thread selection**: `BENCH_MAX_THREADS` caps the OpenMP loop.
- **Analysis**: import the CSV into Python, R, or a spreadsheet to plot time vs. N or vs. process count.

## Quick Troubleshooting

- `benchmark` missing: run `make` at the project root.
- MPI error: ensure `mpicc`/`mpirun` work and `MPI_Init` can start (no mpirun wrapper needed; the binary runs standalone).
- Inconsistent results: keep the system idle; the controller uses `MPI_Barrier` to synchronize MPI timing.

# Exercise 01 - Parallel Series Summation with MPI

## Description

This program calculates the sum of a mathematical series using MPI (Message Passing Interface) to parallelize computations across multiple processes.

### Series Calculation

$$\sum_{i=1}^{N} \frac{1}{i \cdot (1 + i)}$$

### Exact Value

The exact value of this series is:

$$\frac{N}{1 + N}$$

When $N$ is very large, the sum approaches 1.

## Architecture

### Files

- `main.c` : Entry point, MPI management and work distribution
- `utils.c` : Computation and display functions
- `header.h` : Function declarations and includes
- `Makefile` : Compilation and execution

### Main Functions

#### `long double ft_sum(size_t start, size_t end)`
Computes the partial sum of the series for a given interval.
- Uses `long double` to maximize precision (18-21 significant digits)
- Explicit cast to `long double` to avoid precision loss

#### `void ft_display_info(size_t N, long double global_sum)`
Displays results:
- Value of N
- Computed sum (33 decimal places)
- Expected sum (exact value)

## Input Parsing

```c
N = (size_t)strtoull(argv[1], NULL, 10);
```

- `strtoull()`: Converts string to `unsigned long long` (base 10)
- Cast to `size_t` for array indexing and large number support
- Supports values up to $2^{64} - 1$ (18,446,744,073,709,551,615)
- **Note**: No error checking implemented - assumes valid input

## MPI Parallelization

### Work Distribution

Each MPI process computes a portion of the series:

```c
start = (N / size) * rank + 1
end = (rank == size - 1) ? N : (N / size) * (rank + 1)
```

- **Process 0**: computes from $1$ to $\frac{N}{\text{size}}$
- **Process 1**: computes from $\frac{N}{\text{size}} + 1$ to $\frac{2N}{\text{size}}$
- **Process k**: computes from $k \cdot \frac{N}{\text{size}} + 1$ to $(k+1) \cdot \frac{N}{\text{size}}$
- **Last process**: computes up to $N$ (handles division remainder)

### Results Reduction

```c
MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
```

- All processes send their `local_sum` to process 0
- Process 0 receives the total sum in `global_sum`

### Time Measurement

```c
start_time = MPI_Wtime();
// ... computation ...
end_time = MPI_Wtime();
```

Average execution time is calculated and displayed by process 0.

## Compilation and Execution

### Makefile

Configurable variables:
- `NPROC=5` : Number of MPI processes
- `N=1000000000` : Value of N (default 1 billion)

### Commands

```bash
# Compile
make

# Compile and run with default parameters
make run

# Run with custom parameters
mpirun -n 8 ./prog 5000000000

# Clean
make clean    # Removes .o files
make fclean   # Removes everything (including executable)
make re       # Recompile everything
```

## Output Example

```
========================================
N = 1000000000
Computed sum  : 0.999999998999999672934669431301202
Expected sum  : 0.999999999000000001014246825414844
========================================
Computation Time: 0.706608 seconds
```

## Precision and Performance

### `long double` Type
- **Precision**: ~18-21 significant digits (on x86-64)
- **Display format**: `.33Lf` (shows 33 decimals, some may be noise)

### Rounding Errors
Floating-point calculations introduce cumulative rounding errors. To improve precision, we could implement:
- Kahan summation algorithm (compensated summation)
- Pairwise summation
- High-precision arithmetic libraries (GMP)

### Scalability
Theoretical speedup is linear with the number of processes, limited by:
- MPI communication (`MPI_Reduce`)
- Non-uniform work distribution if N is not divisible by the number of processes
- MPI process creation overhead

## Possible Improvements

1. **Load balancing**: Dynamic distribution for non-uniform computations
2. **Precision**: Kahan algorithm implementation
3. **Validation**: Input argument checking
4. **Benchmarking**: Performance comparison based on NPROC
5. **Visualization**: Speedup and parallel efficiency graphs

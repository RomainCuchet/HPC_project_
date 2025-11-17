# HPC Project - Parallel Computing with MPI and OpenMP

## Overview

This project explores parallel programming techniques using **MPI (Message Passing Interface)** and **OpenMP** to solve numerical computation problems. The focus is on understanding parallelization strategies, measuring performance gains (speedup), and analyzing scalability with respect to the number of threads and processes.

## Objectives

The project consists of three main exercises and a theoretical component:

1. **Series Summation**: Calculate and parallelize the computation of $\sum_{i=1}^{n} \frac{1}{i(i+1)}$ using both OpenMP and MPI
2. **Matrix-Vector Multiplication**: Implement and parallelize the product of a tridiagonal matrix with a random vector
3. **MPI Data Structures**: Work with custom data structures (3D points) and MPI communication
4. **Research Analysis**: Study and summarize parallel computation techniques for solving the 2D heat equation

## Key Concepts

- **Parallelization**: Distributing computational workload across multiple processors/threads
- **Performance Analysis**: Measuring speedup and efficiency as the number of processors increases
- **Scalability**: Understanding how algorithms behave with increasing problem sizes (n)
- **MPI vs OpenMP**: 
  - **MPI**: Distributed memory parallelism (multiple processes)
  - **OpenMP**: Shared memory parallelism (multiple threads)

## Project Structure

```
.
├── ex01/          # Exercise 1: Series summation (MPI implementation)
├── ex02/          # Exercise 2: Tridiagonal matrix-vector multiplication
├── ex03/          # Exercise 3: MPI custom data structures
└── README.md      # This file
```

Each exercise directory contains:
- Source code (`.c` files)
- Headers (`.h` files)
- Makefile for compilation and execution
- Dedicated README with detailed explanations

## Performance Metrics

### Speedup
$$S_p = \frac{T_1}{T_p}$$

Where:
- $T_1$ = execution time with 1 processor
- $T_p$ = execution time with $p$ processors
- Ideal speedup: $S_p = p$ (linear)

### Efficiency
$$E_p = \frac{S_p}{p} \times 100\%$$

Perfect efficiency = 100% (rarely achieved due to communication overhead)

## Technologies Used

- **Language**: C
- **Parallel Libraries**: 
  - OpenMPI (MPI implementation)
  - OpenMP (shared memory parallelism)
- **Compiler**: `mpicc` (MPI), `gcc` with `-fopenmp`
- **Tools**: Makefile, performance timing functions

## Getting Started

### Prerequisites

```bash
# Install OpenMPI
sudo apt-get install openmpi-bin openmpi-common libopenmpi-dev

# Verify installation
mpicc --version
mpirun --version
```

### Running Exercises

```bash
# Navigate to an exercise directory
cd ex01/

# Compile
make

# Run with specific number of processes
make run          # Uses default configuration
mpirun -n 8 ./prog 1000000000  # Custom execution
```

## Expected Outcomes

- Understanding of parallel programming paradigms
- Ability to identify parallelizable portions of algorithms
- Skills in performance measurement and analysis
- Knowledge of communication patterns in distributed systems
- Insight into the trade-offs between computation and communication overhead

## References

- MPI Documentation: https://www.open-mpi.org/doc/
- OpenMP Specification: https://www.openmp.org/specifications/
- Research Article: [Parallel computation to bidimensional heat equation using MPI/CUDA and FFTW package](https://doi.org/10.3389/fcomp.2023.1305800)

---

**Authors**: Aurele, ahabbard  
**Course**: High Performance Computing  
**Date**: November 2025

#include <mpi.h>

#include "header.h"

float mpi_sum(size_t N){
    int		size;
    int		rank;

    size_t start;           // start index for this process
    size_t end;             // end index for this process
    long double local_sum;  // sum computed by this process
    long double global_sum; // total sum
    // here argv[1] is converted to an long long int using stroull,
    // then cast to size_t
    // we will use it ton control our make run ARGV= 923370036854775807
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Determine the range of numbers for this process
    start = (N / size) * rank + 1;
    end = (rank == size - 1) ? N : (N / size)
        * (rank + 1);
    // Each process computes its local sum
    // We set a timer to measure computation time
    local_sum = ft_sum(start, end);
    // Reduce all local sums into the global sum at process 0
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0,
        MPI_COMM_WORLD);
    return global_sum;

}
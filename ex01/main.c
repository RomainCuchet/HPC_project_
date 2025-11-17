/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurele <aurele@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:40:13 by aurele            #+#    #+#             */
/*   Updated: 2025/11/24 14:43:07 by aurele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// in the=is program we want to calculate the sum of the series: 1/i*(1+i) for i
// from 1 to N
// we will distribute the computation across multiple MPI processes
// to compare the precision we know that the exact value of the sum is N/(1+N
// when N is large is approximately 1.
int	main(int argc, char **argv)
{
	int		size;
	int		rank;
	double	start_time;
	double	end_time;
	double	total_time;

	size_t N; // total number of slices
	size_t start;           // start index for this process
	size_t end;             // end index for this process
	long double local_sum;  // sum computed by this process
	long double global_sum; // total sum
	N = (size_t)strtoull(argv[1], NULL, 10);
	// here argv[1] is converted to an long long int using stroull,
	// then cast to size_t
	// we will use it ton control our make run ARGV= 923370036854775807
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	// Determine the range of numbers for this process
	start = (N / size) * rank + 1;
	end = (rank == size - 1) ? N : (N / size)
		* (rank + 1);
	// Each process computes its local sum
	// We set a timer to measure computation time
	start_time = MPI_Wtime();
	local_sum = ft_sum(start, end);
	// printf("Process %2d | Local sum: %.18Lf\n", rank, local_sum);
	// Reduce all local sums into the global sum at process 0
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0,
		MPI_COMM_WORLD);
	end_time = MPI_Wtime();
	// let's take the average computation time across all processes
	MPI_Reduce(&end_time, &total_time, 1, MPI_DOUBLE, MPI_SUM, 0,
		MPI_COMM_WORLD);
	total_time /= size;
	if (rank == 0)
	{
		ft_display_info(N, global_sum);
		printf("Computation Time: %.6f seconds\n", total_time);
	}
	MPI_Finalize();
}

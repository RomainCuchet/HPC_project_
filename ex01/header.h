/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabbard <ahabbard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:43:34 by aurele            #+#    #+#             */
/*   Updated: 2025/11/18 22:52:54 by ahabbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <mpi.h>
# include <stdio.h>
# include <stdlib.h>

// ################################ UTILS PROTOTYPES ############################# //

/**
 * @brief compute the sum of the 1/(i*(i+1)) from start to end
 * 
 * This function compute the sum of the 1/(1*(i+1)) summing all factors
 * 
 * @param start the starting rank of the sum
 * @param end the final rank of the sum
 *  
 */
long double	ft_sum(size_t start, size_t end);

/**
 * @brief compute the sum of the 1/(i*(i+1)) from 1 to n
 * 
 * This function compute the sum of the 1/(1*(i+1)) summing all factors
 * 
 * @param n the final rank of the sum
 *  
 */
float sum_iteratif(int sum_i, int stop_i);

// ############################ MPI SUM PROTOTYPES ############################### //

/**
 * @brief Computes the sum of the series 1/(i*(i+1)) for i from 1 to N using MPI.
 *
 * Each MPI process calculates a portion of the sum based on its rank and the total number of processes.
 * The local sums are then reduced to obtain the global sum, which is returned to all processes.
 *
 * @param N The upper limit of the series to sum.
 * @return  The computed global sum of the series from 1 to N.
 */
float mpi_sum(size_t N);

// ############################ OMP SUM PROTOTYPES ############################### //

/**
 * @brief Computes the sum of the series 1/(i*(i+1)) for i from global_start to global_stop using OpenMP.
 *
 * This function parallelizes the summation using OpenMP directives to distribute the workload
 * across multiple threads, improving performance on multi-core systems.
 *
 * @param global_start The starting index of the series to sum.
 * @param global_stop  The ending index of the series to sum (inclusive).
 * @return             The computed sum of the series from global_start to global_stop.
 */
float omp_sum(int global_start, int global_stop);

// ############################ FORMULA SUM PROTOTYPES ############################### //
/**
 * @brief compute the sum of the 1/(i*(i+1)) from 1 to n
 * 
 * This function compute the sum of the 1/(1*(i+1)) using the telescopic sum formula
 * 
 * @param n the final rank of the sum
 *  
 */
float sum_formula(int n);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabbard <ahabbard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:39:56 by aurele            #+#    #+#             */
/*   Updated: 2025/11/18 22:24:51 by ahabbard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long double ft_sum(size_t start, size_t end)
{
    long double sum;
    size_t i;

    i = start;
    sum = 0.0L;
    while (i <= end)
    {
        sum += 1.0L / ((long double)i * (1.0L + (long double)i));
        i++;
    }
    return sum;
}

void ft_display_info(size_t number_of_slice, long double global_sum)
{
    printf("\n========================================\n");
    printf("N = %zu\n", number_of_slice);
    printf("Computed sum  : %.33Lf\n", global_sum);
    printf("Expected sum  : %.33Lf\n",
        (long double)number_of_slice / (1.0L + (long double)number_of_slice));
    printf("========================================\n");
}

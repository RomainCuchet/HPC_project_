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
#include <omp.h>

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

float sum_iteratif(int start_i, int stop_i){
    float sum = 0;
    if(start_i<0 || stop_i<start_i){
        return -1;
    }
    for(int i=start_i; i<=stop_i;i++){
        sum += 1.0f/(i*(i+1.0f));
    }
    return sum;
}


float sum_formula(int n){
    return 1.0f-1.0f/(n+1);
}

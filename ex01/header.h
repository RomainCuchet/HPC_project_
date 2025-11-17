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

long double	ft_sum(size_t start, size_t end);
void		ft_display_info(size_t number_of_slice, long double global_sum);

#endif

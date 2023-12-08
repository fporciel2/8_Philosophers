/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:05:21 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/08 15:17:06 by fporciel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * 'Philosophers' is a simulation program that explores concurrent programming
 * with threads, mutexes and semaphores. It is an implementation of a solution
 * of a variation on the dining philosophers problem by Edsger Dijkstra.
 *
 * Copyright (C) 2023  Federico Porciello
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PHILO_H
# define PHILO_H
//# define _XOPEN_SOURCE 700
# define _DEFAULT_SOURCE
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>
# include <time.h>
# include <sys/types.h>

typedef struct s_philo
{
	long long	nop;
	useconds_t	ttd;
	useconds_t	tte;
	useconds_t	tts;
	long long	notepme;
	int			result;
}				t_philo;

int			phi_init(t_philo *phi, int argc, char **argv);
int			ft_isdigit(char c);
long long	ft_atol(char *nptr);
useconds_t	phi_atoitou(char *nptr);

#endif

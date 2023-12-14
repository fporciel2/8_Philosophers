/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:05:21 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/14 09:59:17 by fporciel         ###   ########.fr       */
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

typedef struct s_name
{
	pthread_t		thread;
	pthread_mutex_t	*lock;
	long long		id;
	int				active;
	long long		fork;
	long long		nop;
	useconds_t		ttd;
	useconds_t		tte;
	useconds_t		tts;
	long long		notepme;
	struct s_name	*prev;
	struct s_name	*next;
}					t_name;

typedef struct s_philo
{
	pthread_mutex_t	lock;
	long long		nop;
	useconds_t		ttd;
	useconds_t		tte;
	useconds_t		tts;
	long long		notepme;
	int				result;
	struct s_name	*philosophers;
	struct timeval	tv;
}					t_philo;

int			phi_init(t_philo *phi, int argc, char **argv);
int			ft_isdigit(char c);
long long	ft_atol(char *nptr);
useconds_t	phi_atoitou(char *nptr);
int			phi_sit_at_table(t_philo *phi);
int			phi_error_sit_at_table(t_philo *phi);
int			phi_clean_table(t_philo *phi);
int			phi_log_taken_fork(t_philo *phi, long long nop);
int			phi_log_eating(t_philo *phi, long long nop);
int			phi_log_sleeping(t_philo *phi, long long nop);
int			phi_log_thinking(t_philo *phi, long long nop);
int			phi_log_died(t_philo *phi, long long nop);
void		*phi_routine(void *philo);
int			phi_init_threads(t_philo *phi);
int			phi_pthread_create_failure(t_philo *phi);

#endif

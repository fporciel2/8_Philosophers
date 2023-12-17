/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_supervisor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:02:02 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/17 09:14:25 by fporciel         ###   ########.fr       */
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

#include "philo.h"

static int	phi_supervisor_loop(t_name *p, unsigned long long start)
{
	unsigned long long	delta;
	unsigned long long	time;

	delta = 0;
	time = 0;
	while (delta < p->ttd)
	{
		if (gettimeofday(&(p->tv), NULL) < 0)
			return (pthread_detach(p->thread), -1);
		time = (unsigned long long)(p->tv.tv_sec) * 1000
			+ (unsigned long long)(p->tv.tv_usec) / 1000;
		delta = time - start;
	}
	if (pthread_mutex_lock(&(p->eat_calm)) != 0)
		return (pthread_detach(p->thread), -1);
	return (1);
}

void	*phi_supervisor(void *philo)
{
	t_name				*p;
	unsigned long long	start;

	p = (t_name *)philo;
	while (1)
	{
		if (gettimeofday(&(p->tv), NULL) < 0)
			return (pthread_detach(p->thread), NULL);
		start = (unsigned long long)(p->tv.tv_sec) * 1000
			+ (unsigned long long)(p->tv.tv_usec) / 1000;
		if (phi_supervisor_loop(p, start) < 0)
			return (NULL);
		if (p->iseating == 0)
		{
			pthread_detach(p->thread);
			return (phi_log_dead((t_philo *)(p->phi), p->id), NULL);
		}
		if (pthread_mutex_unlock(&(p->eat_calm)) != 0)
			return (pthread_detach(p->thread), NULL);
	}
	return (NULL);
}

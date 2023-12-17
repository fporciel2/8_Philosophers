/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_supervisor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:02:02 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/17 16:25:29 by fporciel         ###   ########.fr       */
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

static int	phi_supervisor_check(t_name *p)
{
	if (p->iseating == 0)
	{
		pthread_mutex_lock(p->lock);
		phi_log_dead((t_philo *)(p->phi), p->id);
		pthread_mutex_unlock(p->lock);
		return (-1);
	}
	pthread_mutex_lock(&(p->over));
	if (p->isover == 1)
		return (-1);
	pthread_mutex_unlock(&(p->over));
	return (1);
}

static int	phi_supervisor_loop(t_name *p, unsigned long long start)
{
	unsigned long long	delta;
	unsigned long long	time;

	delta = 0;
	time = 0;
	while (delta < p->ttd)
	{
		if (phi_check_gettime(p))
			return (-1);
		time = (unsigned long long)(p->tv.tv_sec) * 1000
			+ (unsigned long long)(p->tv.tv_usec) / 1000;
		delta = time - start;
	}
	if (phi_check_lock(p, &(p->eat_calm)))
		return (-1);
	return (1);
}

void	*phi_supervisor(void *philo)
{
	t_name				*p;
	unsigned long long	start;

	p = (t_name *)philo;
	while (1)
	{
		if (phi_check_gettime(p))
			return (phi_exit_sup(p));
		start = (unsigned long long)(p->tv.tv_sec) * 1000
			+ (unsigned long long)(p->tv.tv_usec) / 1000;
		if (phi_supervisor_loop(p, start) < 0)
			return (phi_exit_sup(p));
		if (phi_supervisor_check(p) < 0)
			return (phi_exit_sup(p));
		if (phi_check_unlock(p, &(p->eat_calm)))
			return (phi_exit_sup(p));
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_supervisor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:18:14 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/18 12:18:40 by fporciel         ###   ########.fr       */
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

static int	phi_check_iseating(t_name *p)
{
	pthread_mutex_lock(&(p->eat));
	if (p->iseating == 0)
	{
		p->r = phi_log_dead(p->phi, p->id);
		pthread_mutex_unlock(&(p->eat));
		return (1);
	}
	pthread_mutex_unlock(&(p->eat));
	return (0);
}

static int	phi_check_isdead(t_name *p)
{
	pthread_mutex_lock(&(p->dead));
	if (p->isdead == 1)
	{
		pthread_mutex_unlock(&(p->dead));
		return (1);
	}
	pthread_mutex_unlock(&(p->dead));
	return (0);
}

static void	*phi_supervision(t_name *p, unsigned long long start)
{
	unsigned long long	time;
	unsigned long long	delta;

	while (1)
	{
		if (gettimeofday(&(p->tv), NULL) < 0)
			return (pthread_detach(p->thread), NULL);
		time = (unsigned long long)(p->tv.tv_sec) * 1000
			+ (unsigned long long)(p->tv.tv_usec) / 1000;
		delta = time - start;
		if (((delta >= p->ttd) && phi_check_iseating(p))
			|| phi_check_isdead(p))
			return (pthread_detach(p->thread), NULL);
		if (delta >= p->ttd)
		{
			if (gettimeofday(&(p->tv), NULL) < 0)
				return (pthread_detach(p->thread), NULL);
			start = (unsigned long long)(p->tv.tv_sec) * 1000
				+ (unsigned long long)(p->tv.tv_usec) / 1000;
		}
	}
	return (pthread_join(p->thread, NULL), NULL);
}

static void	*phi_start_supervision(t_name *p)
{
	unsigned long long	start;

	if (gettimeofday(&(p->tv), NULL) < 0)
		return (NULL);
	start = (unsigned long long)(p->tv.tv_sec) * 1000
		+ (unsigned long long)(p->tv.tv_usec) / 1000;
	if (pthread_create(&(p->thread), NULL, phi_routine, (void *)p) != 0)
		return (NULL);
	return (phi_supervision(p, start));
}

void	*phi_superv(void *ph)
{
	t_name	*p;
	t_philo	*phi;

	p = (t_name *)ph;
	phi = (t_philo *)(p->phi);
	if (phi->nop == 1)
	{
		if (usleep(p->ttd) < 0)
			return (NULL);
		p->r = phi_log_dead((t_philo *)(p->phi), 1);
		return (NULL);
	}
	return (phi_start_supervision(p));
}

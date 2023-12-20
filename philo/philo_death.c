/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:57:10 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/20 14:21:04 by fporciel         ###   ########.fr       */
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

void	*phi_death(t_name *p)
{
	t_philo	*phi;

	if (pthread_mutex_lock(p->lock) != 0)
		return (NULL);
	phi = (t_philo *)p->phi;
	*(p->deadid) = p->id;
	phi_log_dead(phi, p->id);
	pthread_mutex_unlock(p->lock);
	return (NULL);
}

int	phi_assign_time(t_name *p, unsigned long long *s)
{
	if (gettimeofday(&(p->tv), NULL) < 0)
		return (-1);
	*s = (unsigned long long)(p->tv.tv_sec) * 1000
		+ (unsigned long long)(p->tv.tv_usec) / 1000;
	return (1);
}

int	phi_check_time(t_name *p, unsigned long long *s, unsigned long long *d)
{
	unsigned long long	tmstmp;

	if (gettimeofday(&(p->tv), NULL) < 0)
		return (-1);
	tmstmp = (unsigned long long)(p->tv.tv_sec) * 1000
		+ (unsigned long long)(p->tv.tv_usec) / 1000;
	*d = tmstmp - *s;
	if (*d > p->ttd)
		return (-1);
	return (1);
}

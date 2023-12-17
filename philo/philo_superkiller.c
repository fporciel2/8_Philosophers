/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_superkiller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:04:26 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/17 16:30:18 by fporciel         ###   ########.fr       */
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

int	phi_check_unlock(t_name *p, pthread_mutex_t *m)
{
	if (pthread_mutex_lock(&(p->over)) || (p->isover == 1)
		|| pthread_mutex_unlock(&(p->over))
		|| pthread_mutex_unlock(m))
		return (1);
	return (0);
}

int	phi_check_lock(t_name *p, pthread_mutex_t *m)
{
	if (pthread_mutex_lock(&(p->over)) || (p->isover == 1)
		|| pthread_mutex_unlock(&(p->over))
		|| pthread_mutex_lock(m))
		return (1);
	return (0);
}

int	phi_check_gettime(t_name *p)
{
	if (pthread_mutex_lock(&(p->over)) || (p->isover == 1)
		|| pthread_mutex_unlock(&(p->over))
		|| (gettimeofday(&(p->tv), NULL) < 0))
		return (1);
	return (0);
}

void	*phi_exit_sup(t_name *p)
{
	pthread_mutex_lock(&(p->killer));
	p->kill = 1;
	pthread_mutex_unlock(&(p->killer));
	return (NULL);
}

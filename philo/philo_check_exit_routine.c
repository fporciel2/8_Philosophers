/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_exit_routine.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:16:08 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/17 15:24:22 by fporciel         ###   ########.fr       */
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

int	phi_check_lock_routine(t_name *p, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(&(p->killer)) || (p->kill == 1)
		|| pthread_mutex_unlock(&(p->killer))
		|| pthread_mutex_lock(mutex))
		return (1);
	return (0);
}

int	phi_check_unlock_routine(t_name *p, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(&(p->killer)) || (p->kill == 1)
		|| pthread_mutex_unlock(&(p->killer))
		|| pthread_mutex_unlock(mutex))
		return (1);
	return (0);
}

void	*phi_exit_routine(t_name *p)
{
	pthread_mutex_lock(&(p->over));
	p->isover = 1;
	pthread_mutex_unlock(&(p->over));
	return (NULL);
}

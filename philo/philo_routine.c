/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:04:10 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/15 15:29:22 by fporciel         ###   ########.fr       */
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

static void	*phi_notepme_routine(t_name *philo)
{
}

static void	*phi_normal_routine(t_name *philo)
{
	unsigned long long	time;
	
	while (1)
	{
		if (gettimeofday(&(philo->tv), NULL) < 0)
			return (phi_gettime_routine_failure(philo));
	}
}

void	*phi_routine(void *philo)
{
	if (pthread_create(&(((t_name *)philo)->supervisor), NULL,
				phi_supervisor, philo) != 0)
		return ((void *)phi_suprevisor_start_failure((t_name *)philo));
	if (pthread_create(&(((t_name *)philo)->monitor), NULL,
				phi_monitor, philo) != 0)
		return ((void *)phi_monitor_start_failure((t_name *)philo));
	if ((((t_name *)philo)->notepme) < 0)
		return (phi_normal_routine((t_name *)philo));
	else
		return (phi_notepme_routine((t_name *)philo));
}

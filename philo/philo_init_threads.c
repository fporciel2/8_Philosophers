/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:39:55 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/13 15:24:57 by fporciel         ###   ########.fr       */
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

int	phi_init_threads(t_philo *phi)
{
	t_name	*tmp;

	tmp = phi->philosophers;
	if ((pthread_create(&(tmp->thread), NULL, phi_routine, (void *)tmp) != 0)
		|| (pthread_join(tmp->thread, NULL) != 0))
	{
		tmp->active = 0;
		return (phi_pthread_create_failure(phi));
	}
	tmp->active = 1;
	tmp = tmp->next;
	while (tmp && (tmp != phi->philosophers))
	{
		if ((pthread_create(&(tmp->thread), NULL,
					phi_routine, (void *)tmp) != 0)
			|| (pthread_join(tmp->thread, NULL) != 0))
		{
			tmp->active = 0;
			return (phi_pthread_create_failure(phi));
		}
		tmp->active = 1;
		tmp = tmp->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pthread_create_failure.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:59:49 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/16 14:00:01 by fporciel         ###   ########.fr       */
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

int	phi_pthread_create_failure(t_philo *phi)
{
	t_name	*tmp;

	tmp = phi->philosophers;
	if (tmp->active != 0)
	{
		if (pthread_detach(tmp->thread) != 0)
			printf("Warning: cannot detach philosopher %lld!\n\n", tmp->id);
	}
	tmp = tmp->next;
	while (tmp && (tmp != phi->philosophers))
	{
		if (tmp->active != 0)
		{
			if (pthread_detach(tmp->thread) != 0)
				printf("Warning: cannot detach philosopher %lld!\n\n", tmp->id);
		}
		tmp = tmp->next;
	}
	return (phi_error_sit_at_table(phi));
}

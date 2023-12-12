/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sit_at_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:38:03 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/12 13:46:30 by fporciel         ###   ########.fr       */
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

static int	phi_init_threads(t_philo *phi)
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
		if ((pthread_create(&(tmp->thread), NULL, phi_routine, (void *)tmp) != 0)
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

static int	phi_be_comforted(t_philo *phi, t_name *iter)
{
	if (phi->nop > 1)
	{
		iter->next = phi->philosophers;
		phi->philosophers->prev = iter;
	}
	else
	{
		phi->philosophers->prev = NULL;
		phi->philosophers->next = NULL;
	}
	return (phi_init_threads(phi));
}

int	phi_sit_at_table(t_philo *phi)
{
	long long	count;
	t_name		*iter;
	t_name		*previter;
	long long	i;

	count = phi->nop;
	i = 1;
	phi->philosophers = (t_name *)malloc(sizeof(t_name));
	if (phi->philosophers == NULL)
		return (-1);
	iter = phi->philosophers;
	iter->id = i;
	count--;
	while (count != 0)
	{
		previter = iter;
		iter->next = (t_name *)malloc(sizeof(t_name));
		if (iter->next == NULL)
			return (phi_error_sit_at_table(phi));
		iter = iter->next;
		iter->id = ++i;
		iter->prev = previter;
		count--;
	}
	return (phi_be_comforted(phi, iter));
}

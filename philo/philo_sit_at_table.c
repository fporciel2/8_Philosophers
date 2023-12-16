/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sit_at_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:38:03 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/16 15:23:37 by fporciel         ###   ########.fr       */
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

static int	phi_init_internal_checkers(t_name *head)
{
	unsigned long long	i;
	t_name				*tmp;

	i = 0;
	tmp = head;
	while ((tmp && (tmp != head)) || (i == 0))
	{
		tmp->i = 0;
		tmp->iseating = 0;
		tmp->issleeping = 0;
		tmp->isthinking = 0;
		tmp = tmp->next;
		i++;
	}
	return (1);
}

static int	phi_assign_values(t_name *head, t_philo *phi)
{
	unsigned long long	i;
	t_name				*tmp;

	i = 0;
	tmp = head;
	while ((tmp && (tmp != head)) || (i == 0))
	{
		if (pthread_mutex_init(&(tmp->fork), NULL) != 0)
			return (phi_error_sit_at_table(phi));
		tmp->nop = phi->nop;
		tmp->ttd = phi->ttd;
		tmp->tte = phi->tte;
		tmp->tts = phi->tts;
		tmp->notepme = phi->notepme;
		tmp->lock = &(phi->lock);
		tmp->phi = (void *)phi;
		i++;
		tmp = tmp->next;
	}
	return (phi_init_internal_checkers(head));
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
	return (phi_assign_values(phi->philosophers, phi));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_selection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:19:55 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/19 15:31:06 by fporciel         ###   ########.fr       */
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

int	phi_select_first_fork(t_name *p)
{
	if (p->prevfork < p->nextfork)
	{
		if (pthread_mutex_lock(&(p->prev->fork)) != 0)
			return (-1);
		return (1);
	}
	else
	{
		if (pthread_mutex_lock(&(p->next->fork)) != 0)
			return (-1);
		return (1);
	}
}

int	phi_select_second_fork(t_name *p)
{
	if (p->prevfork < p->nextfork)
	{
		if (pthread_mutex_lock(&(p->prev->fork)) != 0)
			return (-1);
		return (1);
	}
	else
	{
		if (pthread_mutex_lock(&(p->next->fork)) != 0)
			return (-1);
		return (1);
	}
}

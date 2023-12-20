/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error_sit_at_table.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:42:57 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/20 12:55:48 by fporciel         ###   ########.fr       */
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

int	phi_error_sit_at_table(t_philo *phi)
{
	t_name	*i;
	t_name	*j;

	i = phi->philosophers;
	while (i)
	{
		j = i->next;
		free(i);
		i = j;
	}
	return (-1);
}

int	phi_bad_sitting(t_philo *phi, t_name *tmp)
{
	t_name	*i;
	t_name	*j;

	i = phi->philosophers;
	j = NULL;
	while (i && ((i != tmp) || ((j == NULL) && (i != j))))
	{
		j = i->next;
		pthread_mutex_destroy(&(i->fork));
		i = j;
	}
	return (phi_error_sit_at_table(phi));
}

int	phi_bad_checking(t_philo *phi, t_name *tmp, int param)
{
	t_name	*i;
	t_name	*j;

	i = phi->philosophers;
	j = NULL;
	while (i && ((i != tmp) || ((j == NULL) && (i != j))))
	{
		j = i->next;
		pthread_mutex_destroy(&(i->eat));
		(void)param;
		i = j;
	}
	return (phi_bad_sitting(phi, phi->philosophers));
}

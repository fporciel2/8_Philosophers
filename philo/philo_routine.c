/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:03:04 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/20 14:17:51 by fporciel         ###   ########.fr       */
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

static void	*phi_abnormal_routine(t_name *p, long long val, t_philo *phi)
{
	unsigned long long	start;
	unsigned long long	delta;

	start = 0;
	if (phi_assign_time(p, &start) < 0)
		return (phi_isover(p));
	while (val)
	{
		val--;
	}
	return (phi_isover(p));
}

static void	*phi_normal_routine(t_name *p, t_philo *phi)
{
	unsigned long long	start;
	unsigned long long	delta;

	start = 0;
	if (phi_assign_time(p, &start) < 0)
		return (phi_isover(p));
	while (1)
	{
		if ((phi_check_time(p, &start, &delta) < 0)
			|| (pthread_mutex_lock(&(p->prev->fork)) != 0)
			|| (phi_log_taken_fork(phi, p->id) < 0)
			|| (pthread_mutex_lock(&(p->next->fork)) != 0)
	}
	return (phi_isover(p));
}

void	*phi_routine(void *ph)
{
	t_name	*p;
	t_philo	*phi;

	p = (t_name *)ph;
	phi = (t_philo *)p->phi;
	if ((p->next == NULL) || (p->prev == NULL))
	{
		usleep(p->ttd);
		return (phi_death(p));
	}
	else if (p->notepme < 0)
		return (phi_normal_routine(p, phi));
	else
		return (phi_abnormal_routine(p, p->notepme, phi));
}

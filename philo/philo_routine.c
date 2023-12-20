/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:03:04 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/20 11:44:40 by fporciel         ###   ########.fr       */
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

static void	*phi_end_routine(t_name *p)
{
	if ((pthread_mutex_lock(p->lock) != 0)
		|| (phi_log_sleeping(p->phi, p->id) < 0)
		|| (pthread_mutex_unlock(p->lock) != 0)
		|| (usleep(p->tts) < 0)
		|| (pthread_mutex_lock(p->lock) != 0)
		|| (phi_log_thinking(p->phi, p->id) < 0)
		|| (pthread_mutex_unlock(p->lock) != 0))
		return (phi_death(p));
	return (p->phi);
}

static void	*phi_continue_routine(t_name *p)
{
	if ((pthread_mutex_lock(p->lock) != 0)
		|| (phi_log_eating(p->phi, p->id) < 0)
		|| (pthread_mutex_unlock(p->lock) != 0)
		|| (usleep(p->tte) < 0)
		|| (pthread_mutex_lock(&(p->eat)) != 0))
		return (phi_death(p));
	p->iseating = 0;
	if ((pthread_mutex_unlock(&(p->eat)) != 0)
		|| (pthread_mutex_unlock(&(p->next->fork)) != 0)
		|| (pthread_mutex_unlock(&(p->prev->fork)) != 0)
		|| (phi_end_routine(p) != p->phi))
		return (phi_death(p));
	return (p->phi);
}

static void	*phi_abnormal_routine(t_name *p, long long val)
{
	while (val)
	{
		if ((pthread_mutex_lock(&(p->prev->fork)) != 0)
			|| (pthread_mutex_lock(p->lock) != 0)
			|| (phi_log_taken_fork(p->phi, p->id) < 0)
			|| (pthread_mutex_unlock(p->lock) != 0)
			|| (pthread_mutex_lock(&(p->next->fork)) != 0)
			|| (pthread_mutex_lock(p->lock) != 0)
			|| (phi_log_taken_fork(p->phi, p->id) < 0)
			|| (pthread_mutex_unlock(p->lock) != 0)
			|| (pthread_mutex_lock(&(p->eat)) != 0))
			return (phi_death(p));
		p->iseating = 1;
		if ((pthread_mutex_unlock(&(p->eat)) != 0)
			|| (phi_continue_routine(p) != p->phi))
			return (phi_death(p));
		val--;
	}
	return (phi_death(p));
}

static void	*phi_normal_routine(t_name *p)
{
	while (1)
	{
		if ((phi_select_first_fork(p) < 0)
			|| (pthread_mutex_lock(p->lock) != 0)
			|| (phi_log_taken_fork(p->phi, p->id) < 0)
			|| (pthread_mutex_unlock(p->lock) != 0)
			|| (phi_select_second_fork(p) < 0)
			|| (pthread_mutex_lock(p->lock) != 0)
			|| (phi_log_taken_fork(p->phi, p->id) < 0)
			|| (pthread_mutex_unlock(p->lock) != 0)
			|| (pthread_mutex_lock(&(p->eat)) != 0))
			return (phi_death(p));
		p->iseating = 1;
		if ((pthread_mutex_unlock(&(p->eat)) != 0)
			|| (phi_continue_routine(p) != p->phi))
			return (phi_death(p));
	}
	return (phi_death(p));
}

void	*phi_routine(void *ph)
{
	t_name	*p;

	p = (t_name *)ph;
	if (p->notepme < 0)
		return (phi_normal_routine(p));
	else
		return (phi_abnormal_routine(p, p->notepme));
}

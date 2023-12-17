/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:04:10 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/17 16:02:39 by fporciel         ###   ########.fr       */
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

static int	phi_end_routine(t_name *philo)
{
	if (phi_check_unlock_routine(philo, &(philo->prev->fork)))
		return (-1);
	philo->haspfork = 0;
	if (phi_check_lock_routine(philo, philo->lock))
		return (-1);
	if (phi_log_sleeping((t_philo *)(philo->phi), philo->id) < 0)
		return (-1);
	philo->issleeping = 1;
	if (phi_check_unlock_routine(philo, philo->lock))
		return (-1);
	if (usleep(philo->tts) < 0)
		return (-1);
	if (phi_check_lock_routine(philo, philo->lock))
		return (-1);
	philo->issleeping = 0;
	if (phi_log_thinking((t_philo *)(philo->phi), philo->id) < 0)
		return (-1);
	philo->isthinking = 1;
	if (phi_check_unlock_routine(philo, philo->lock))
		return (-1);
	return (1);
}

static int	phi_continue_routine(t_name *philo)
{
	if (phi_check_unlock_routine(philo, philo->lock))
		return (-1);
	if (phi_check_lock_routine(philo, philo->lock))
		return (-1);
	if (phi_log_eating((t_philo *)(philo->phi), philo->id) < 0)
		return (-1);
	if (phi_check_unlock_routine(philo, philo->lock))
		return (-1);
	if (phi_check_lock_routine(philo, &(philo->eat_calm)))
		return (-1);
	philo->iseating = 1;
	if (usleep(philo->tte) < 0)
		return (-1);
	if (phi_check_unlock_routine(philo, &(philo->eat_calm)))
		return (-1);
	philo->iseating = 0;
	if (phi_check_unlock_routine(philo, &(philo->next->fork)))
		return (-1);
	philo->hasnfork = 0;
	return (phi_end_routine(philo));
}

static void	*phi_notepme_routine(t_name *philo)
{
	while ((philo->i)++ < philo->notepme)
	{
		if (phi_check_lock_routine(philo, &(philo->prev->fork)))
			return (phi_exit_routine(philo));
		philo->isthinking = 0;
		if (phi_check_lock_routine(philo, philo->lock))
			return (phi_exit_routine(philo));
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (phi_exit_routine(philo));
		philo->haspfork = 1;
		if (phi_check_unlock_routine(philo, philo->lock))
			return (phi_exit_routine(philo));
		if (phi_check_lock_routine(philo, &(philo->next->fork)))
			return (phi_exit_routine(philo));
		if (phi_check_lock_routine(philo, philo->lock))
			return (phi_exit_routine(philo));
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (phi_exit_routine(philo));
		philo->hasnfork = 1;
		if (phi_continue_routine(philo) < 0)
			return (phi_exit_routine(philo));
	}
	return (phi_exit_routine(philo));
}

static void	*phi_normal_routine(t_name *philo)
{
	while (1)
	{
		if (phi_check_lock_routine(philo, &(philo->prev->fork)))
			return (phi_exit_routine(philo));
		philo->isthinking = 0;
		if (phi_check_lock_routine(philo, philo->lock))
			return (phi_exit_routine(philo));
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (phi_exit_routine(philo));
		philo->haspfork = 1;
		if (phi_check_unlock_routine(philo, philo->lock))
			return (phi_exit_routine(philo));
		if (phi_check_lock_routine(philo, &(philo->next->fork)))
			return (phi_exit_routine(philo));
		if (phi_check_lock_routine(philo, philo->lock))
			return (phi_exit_routine(philo));
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (phi_exit_routine(philo));
		philo->hasnfork = 1;
		if (phi_continue_routine(philo) < 0)
			return (phi_exit_routine(philo));
	}
	return (phi_exit_routine(philo));
}

void	*phi_routine(void *philo)
{
	t_name	*p;

	p = (t_name *)philo;
	if ((p->prev == NULL) || (p->next == NULL))
	{
		pthread_create(&(p->supervisor), NULL, phi_supervisor, (void *)p);
		usleep(p->ttd);
	}
	else if (p->notepme < 0)
	{
		pthread_create(&(p->supervisor), NULL, phi_supervisor, (void *)p);
		return (phi_normal_routine((t_name *)philo));
	}
	else
	{
		pthread_create(&(p->supervisor), NULL, phi_supervisor, (void *)p);
		return (phi_notepme_routine((t_name *)philo));
	}
	pthread_join(p->supervisor, NULL);
	return (NULL);
}

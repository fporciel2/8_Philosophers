/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:04:10 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/17 09:05:47 by fporciel         ###   ########.fr       */
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
	philo->haspfork = 0;
	if (pthread_mutex_lock(philo->lock) != 0)
		return (pthread_detach(philo->supervisor), -1);
	if (phi_log_sleeping((t_philo *)(philo->phi), philo->id) < 0)
		return (pthread_detach(philo->supervisor), -1);
	philo->issleeping = 1;
	if (pthread_mutex_unlock(philo->lock) != 0)
		return (pthread_detach(philo->supervisor), -1);
	if (usleep(philo->tts) < 0)
		return (pthread_detach(philo->supervisor), -1);
	if (pthread_mutex_lock(philo->lock) != 0)
		return (pthread_detach(philo->supervisor), -1);
	philo->issleeping = 0;
	if (phi_log_thinking((t_philo *)(philo->phi), philo->id) < 0)
		return (pthread_detach(philo->supervisor), -1);
	philo->isthinking = 1;
	if (pthread_mutex_unlock(philo->lock) != 0)
		return (pthread_detach(philo->supervisor), -1);
	return (1);
}

static int	phi_continue_routine(t_name *philo)
{
	if (pthread_mutex_lock(philo->lock) != 0)
		return (pthread_detach(philo->supervisor), -1);
	if (phi_log_eating((t_philo *)(philo->phi), philo->id) < 0)
		return (pthread_detach(philo->supervisor), -1);
	if (pthread_mutex_unlock(philo->lock) != 0)
		return (pthread_detach(philo->supervisor), -1);
	if (pthread_mutex_lock(&(philo->eat_calm)) != 0)
		return (pthread_detach(philo->supervisor), -1);
	philo->iseating = 1;
	if (usleep(philo->tte) < 0)
		return (pthread_detach(philo->supervisor), -1);
	if (pthread_mutex_unlock(&(philo->eat_calm)) != 0)
		return (pthread_detach(philo->supervisor), -1);
	philo->iseating = 0;
	if (pthread_mutex_unlock(&(philo->next->fork)) != 0)
		return (pthread_detach(philo->supervisor), -1);
	philo->hasnfork = 0;
	if (pthread_mutex_unlock(&(philo->prev->fork)) != 0)
		return (pthread_detach(philo->supervisor), -1);
	return (phi_end_routine(philo));
}

static void	*phi_notepme_routine(t_name *philo)
{
	while ((philo->i)++ < philo->notepme)
	{
		if (pthread_mutex_lock(&(philo->prev->fork)) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		philo->isthinking = 0;
		if (pthread_mutex_lock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (pthread_detach(philo->supervisor), NULL);
		philo->haspfork = 1;
		if (pthread_mutex_unlock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (pthread_mutex_lock(&(philo->next->fork)) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (pthread_mutex_lock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (pthread_detach(philo->supervisor), NULL);
		philo->hasnfork = 1;
		if (pthread_mutex_unlock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (phi_continue_routine(philo) < 0)
			return (NULL);
	}
	return (pthread_detach(philo->supervisor), NULL);
}

static void	*phi_normal_routine(t_name *philo)
{
	while (1)
	{
		if (pthread_mutex_lock(&(philo->prev->fork)) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		philo->isthinking = 0;
		if (pthread_mutex_lock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (pthread_detach(philo->supervisor), NULL);
		philo->haspfork = 1;
		if (pthread_mutex_unlock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (pthread_mutex_lock(&(philo->next->fork)) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (pthread_mutex_lock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (phi_log_taken_fork((t_philo *)(philo->phi), philo->id) < 0)
			return (pthread_detach(philo->supervisor), NULL);
		philo->hasnfork = 1;
		if (pthread_mutex_unlock(philo->lock) != 0)
			return (pthread_detach(philo->supervisor), NULL);
		if (phi_continue_routine(philo) < 0)
			return (NULL);
	}
	return (pthread_detach(philo->supervisor), NULL);
}

void	*phi_routine(void *philo)
{
	if (((((t_name *)philo)->prev) == NULL)
		|| ((((t_name *)philo)->next) == NULL))
	{
		if (pthread_create(&(((t_name *)philo)->supervisor), NULL,
				phi_supervisor, (void *)philo) != 0)
			return (NULL);
		if (usleep(((t_name *)philo)->ttd) < 0)
			return (pthread_detach(((t_name *)philo)->supervisor), NULL);
	}
	else if ((((t_name *)philo)->notepme) < 0)
	{
		if (pthread_create(&(((t_name *)philo)->supervisor), NULL,
				phi_supervisor, (void *)philo) != 0)
			return (NULL);
		return (phi_normal_routine((t_name *)philo));
	}
	else
	{
		if (pthread_create(&(((t_name *)philo)->supervisor), NULL,
				phi_supervisor, (void *)philo) != 0)
			return (NULL);
		return (phi_notepme_routine((t_name *)philo));
	}
	return (NULL);
}

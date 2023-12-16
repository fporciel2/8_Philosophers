/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_logs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:42:17 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/16 14:44:35 by fporciel         ###   ########.fr       */
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

int	phi_log_taken_fork(t_philo *phi, long long nop)
{
	unsigned long long	tmstmp;

	if (gettimeofday(&(phi->tv), NULL) < 0)
		return (-1);
	tmstmp = (unsigned long long)(phi->tv.tv_sec) * 1000
		+ (unsigned long long)(phi->tv.tv_usec) / 1000;
	return (printf("\n%llu %lld has taken a fork", tmstmp, nop));
}

int	phi_log_eating(t_philo *phi, long long nop)
{
	unsigned long long	tmstmp;

	if (gettimeofday(&(phi->tv), NULL) < 0)
		return (-1);
	tmstmp = (unsigned long long)(phi->tv.tv_sec) * 1000
		+ (unsigned long long)(phi->tv.tv_usec) / 1000;
	return (printf("\n%llu %lld is eating", tmstmp, nop));
}

int	phi_log_sleeping(t_philo *phi, long long nop)
{
	unsigned long long	tmstmp;

	if (gettimeofday(&(phi->tv), NULL) < 0)
		return (-1);
	tmstmp = (unsigned long long)(phi->tv.tv_sec) * 1000
		+ (unsigned long long)(phi->tv.tv_usec) / 1000;
	return (printf("\n%llu %lld is sleeping", tmstmp, nop));
}

int	phi_log_thinking(t_philo *phi, long long nop)
{
	unsigned long long	tmstmp;

	if (gettimeofday(&(phi->tv), NULL) < 0)
		return (-1);
	tmstmp = (unsigned long long)(phi->tv.tv_sec) * 1000
		+ (unsigned long long)(phi->tv.tv_usec) / 1000;
	return (printf("\n%llu %lld is thinking", tmstmp, nop));
}

int	phi_log_dead(t_philo *phi, long long nop)
{
	unsigned long long	tmstmp;

	if (gettimeofday(&(phi->tv), NULL) < 0)
		return (-1);
	tmstmp = (unsigned long long)(phi->tv.tv_sec) * 1000
		+ (unsigned long long)(phi->tv.tv_usec) / 1000;
	return (printf("\n%llu %lld is dead", tmstmp, nop));
}

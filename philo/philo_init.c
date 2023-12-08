/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:36:28 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/08 14:07:13 by fporciel         ###   ########.fr       */
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

static long long	phi_check_input(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (i);
}

int	phi_init(t_philo *phi, int argc, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (phi_check_input(argv[i]) < 0)
			return (-1);
		i++;
	}
	if (argc == 5)
		phi->notepme = ft_atol(argv[4]);
	phi->nop = ft_atol(argv[0]);
	phi->ttd = phi_atou(phi_atom(argv[1]));
	phi->tte = phi_atou(phi_atom(argv[2]));
	phi->tts = phi_atou(phi_atom(argv[3]));
	return (i);
}

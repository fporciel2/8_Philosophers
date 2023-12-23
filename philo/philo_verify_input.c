/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_verify_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 09:58:46 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/23 10:19:06 by fporciel         ###   ########.fr       */
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

static size_t	phi_checker(char *str)
{
	size_t	strlen;

	strlen = 0;
	if (!str)
		return (strlen);
	while (str[strlen])
	{
		if ((str[strlen] < 48) || (str[strlen] > 57))
			return (0);
		strlen++;
	}
	return (strlen);
}

int	phi_verify_input(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		if (!phi_checker(argv[i]))
			return (0);
		i++;
	}
	return (i);
}

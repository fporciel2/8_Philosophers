/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoitou.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:12:50 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/08 14:21:59 by fporciel         ###   ########.fr       */
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

static useconds_t	phi_power(useconds_t base, useconds_t exp)
{
	useconds_t	power;
	useconds_t	cpower;

	if ((base == 0) && (exp != 0))
		return (0);
	else if (exp == 0)
		return (1);
	else
	{
		power = 1;
		cpower = base;
		while (exp)
		{
			if (exp & 1)
				power *= cpower;
			cpower *= cpower;
			exp >>= 1;
		}
	}
	return (power);
}

useconds_t	phi_atoitou(char *nptr)
{
	useconds_t	i;
	useconds_t	j;
	useconds_t	num;
	useconds_t	exp;

	i = 0;
	num = 0;
	j = 0;
	while (ft_isdigit(nptr[i]))
		i++;
	exp = ((i - j) - 1);
	while (j < i)
	{
		num = num + ((nptr[j] - 48) * phi_power(10, exp));
		exp--;
		j++;
	}
	return (num * 1000);
}

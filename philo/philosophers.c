/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:13:06 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/08 14:30:35 by fporciel         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	static t_philo	phi;

	if ((argc < 5) || (argc > 6))
		return (0);
	argc--;
	argv++;
	phi.result = phi_init(&phi, argc, argv);
	if (phi.result < 0)
		return (phi.result);
	printf("\nNumber of philosophers: %lld\n\n", phi.nop);
	printf("Time to die: %llu\n\n", phi.ttd);
	printf("Time to eat: %llu\n\n", phi.tte);
	printf("Time to sleep: %llu\n\n", phi.tts);
	printf("Number of times each philosopher must eat: %lld\n\n", phi.notepme);
	return (phi.result);
}

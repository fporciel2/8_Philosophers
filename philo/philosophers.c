/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:13:06 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/16 15:12:31 by fporciel         ###   ########.fr       */
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

static int	phi_start_dinner(t_philo *phi)
{
	if ((pthread_mutex_init(&(phi->lock), NULL) != 0)
		|| (phi_sit_at_table(phi) < 0) || (phi_init_threads(phi) < 0))
		return (pthread_mutex_destroy(&(phi->lock)));
	return (phi_clean_table(phi));
}

static int	phi_check_input_correctness(t_philo *phi)
{
	if (phi->nop == 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	static t_philo	phi;

	if ((argc < 5) || (argc > 6))
		return (0);
	argc--;
	argv++;
	phi.result = phi_init(&phi, argc, argv);
	if ((phi.result < 0) || (!phi_check_input_correctness(&phi)))
		return (phi.result);
	if (argc == 4)
		phi.notepme = -1;
	return (phi_start_dinner(&phi));
}

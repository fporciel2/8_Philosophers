/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 10:53:52 by fporciel          #+#    #+#             */
/*   Updated: 2023/12/31 12:04:36 by fporciel         ###   ########.fr       */
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

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <time.h>
# include <sys/types.h>
# include <stddef.h>

# define	ERROR	1
# define	MERROR	2
# define	FORK	"has taken a fork"
# define	THINK	"is thinking"
# define	SLEEP	"is sleeping"
# define	EAT		"is eating"
# define	DEAD	"is dead"

typedef struct s_data
{
	int			nop;
	useconds_t	ttd;
	useconds_t	tte;
	useconds_t	tts;
	int			nte;
}				t_data;

typedef struct s_p
{
	struct s_table	*t;
	pthread_t		philosopher;
	int				id;
	int				num_eat;
	bool			isalive;
	bool			iseating;
	bool			hasfinished;
	useconds_t		last_tte;
	useconds_t		tte;
	useconds_t		ttd;
	useconds_t		tte;
	useconds_t		tts;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	state;
	pthread_mutex_t	eat;
	pthread_mutex_t	last_eat;
}					t_p;

typedef struct s_table
{
	t_p				*philosophers;
	size_t			philen;
	size_t			eat_num;
	bool			death;
	bool			end;
	useconds_t		ttd;
	useconds_t		tte;
	useconds_t		tts;
	u_int64_t		start;
	pthread_t		god;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	log;
}					t_table;

int					phi_isdigit(char c);
unsigned long long	phi_atoull(char *str);
useconds_t			phi_time_convert(unsigned long long time);
int					phi_usleep(u_int64_t sleep_time);
u_int64_t			phi_gettime(void);
int					phi_set_up(t_data *input, t_table *init);
void				phi_show_data(t_data *input, int param);
void				phi_show_table(t_table *init);
void				phi_parse(t_data *input, char **argv);
void				phi_init(t_table *t, int nte);
void				*phi_routine(void *param);
void				phi_delete(t_table *t);
void				*phi_god(void *param);
void				phi_exit(int p);
int					phi_eat(t_p *p);
u_int64_t			phi_log(t_table *t, int id, char *action);
int					phi_check(t_data *input);
int					phi_parse_table(t_table *t);
void				phi_monitor_aux(t_data *input, int param, t_table *t);

#endif

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 13:45:55 by fporciel          #+#    #+#              #
#    Updated: 2023/12/08 09:23:54 by fporciel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# 'Philosophers' is a simulation program that explores concurrent programming
# with threads, mutexes and semaphores. It is an implementation of a solution
# of a variation on the dining philosophers problem by Edsger Dijkstra.
#
# Copyright (C) 2023  fporciel
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# You can contact the author at: 
#- fporciel@student.42roma.it
#

.PHONY: all autogit
.DEFAULT_GOAL: all
NAME := philo
DIR := $(shell pwd)
SRCS := $(wildcard philo*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
HDR := philo.h
CC := gcc
CFLAGS := -std=c17 -pedantic-errors -Wall -Wextra -Werror -g \
		  $(addprefix -I, $(DIR))
LDLIBS := $(addprefix -L, $(DIR))
LDFLAGS := -lc -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) $(LDFLAGS) -o $(NAME)

$(OBJS): $(SRCS) $(HDR)
	$(CC) $(CFLAGS) -c $(SRCS) $(HDR)
	rm -f philo.h.gch

autogit:
	cd .. && make autogit && cd philo


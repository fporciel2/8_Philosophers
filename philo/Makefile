# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 13:45:55 by fporciel          #+#    #+#              #
#    Updated: 2023/12/16 14:58:39 by fporciel         ###   ########.fr        #
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

.PHONY: all clean fclean re autogit memcheck helgrind drd
.DEFAULT_GOAL: all
NAME := philo
DIR := $(shell pwd)
SRCS := $(wildcard philo*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
HDR := philo.h
CC := gcc
CFLAGS := -std=c17 -pedantic-errors -Wall -Wextra -Werror -O3 -march=native -g \
		  $(addprefix -I, $(DIR))
LDLIBS := $(addprefix -L, $(DIR))
LDFLAGS := -lc -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) $(LDFLAGS) -o $(NAME)

$(OBJS): $(SRCS) $(HDR)
	$(CC) $(CFLAGS) -c $(SRCS) $(HDR)

clean:
	rm -f $(OBJS)
	rm -f $(HDR).gch

fclean: clean
	rm -f $(NAME)

re: clean fclean all

autogit: fclean
	cd ..
	git status
	git add *
	git status
	echo "\nPlease, enter your commit message:"
	read commit_message; git commit -m "$$commit_message"
	git status
	git push
	cd philo

memcheck:
	@echo "\nPlease, enter your input to test:"
	@read input; \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--show-error-list=yes -s -v ./philo $$input

helgrind:
	@echo "\nPlease, enter your input to test:"
	@read input; \
		valgrind --tool=helgrind --history-level=full --read-var-info=yes \
		-s ./philo $$input

drd:
	@echo "\nPlease, enter your input to test:"
	@read input; \
		valgrind --tool=drd --check-stack-var=yes --show-stack-usage=yes \
		./philo $$input


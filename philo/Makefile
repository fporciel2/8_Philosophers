# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 13:45:55 by fporciel          #+#    #+#              #
#    Updated: 2023/12/17 11:22:03 by fporciel         ###   ########.fr        #
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

.PHONY: all clean fclean re autogit asan tsan
.DEFAULT_GOAL: all
NAME := philo
DIR := $(shell pwd)
SRCS := $(wildcard philo*.c)
OBJS := $(patsubst %.c, %.o, $(SRCS))
HDR := philo.h
CC := gcc
CFLAGS := -std=c17 -pedantic-errors -Wall -Wextra -Werror -pthread \
		  -O3 -march=native -g \
		  $(addprefix -I, $(DIR))
LDLIBS := $(addprefix -L, $(DIR))
LDFLAGS := -lc -lpthread

all: $(NAME)

asan: CFLAGS := -std=c17 -pedantic-errors -Wall -Wextra -Werror \
	-fsanitize=address -pthread -O3 -march=native -g \
	$(addprefix -I, $(DIR))

asan: all

tsan: CFLAGS := -std=c17 -pedantic-errors -Wall -Wextra -Werror \
	-fsanitize=thread -pthread -O3 -march=native -g \
	$(addprefix -I, $(DIR))

tsan: all

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
	git status
	git add *
	git status
	echo "\nPlease, enter your commit message:"
	read commit_message; git commit -m "$$commit_message"
	git status
	git push


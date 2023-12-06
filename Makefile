# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fporciel <fporciel@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 11:21:05 by fporciel          #+#    #+#              #
#    Updated: 2023/12/06 13:43:57 by fporciel         ###   ########.fr        #
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

.PHONY: all bonus clean fclean re rebonus autogit memcheck helgrind \
	bmemcheck bhelgrind
.DEFAULT_GOAL: all
DIR := $(shell pwd)
NAMEDIR := $(DIR)/philo
BDIR := $(DIR)/philo_bonus
NAME := $(NAMEDIR)/philo
BNAME := $(BDIR)/philo_bonus
OBJS := $(wildcard **/*.o)
LIBS := $(wildcard **/*.a)

all: $(NAME)

bonus: $(BNAME)

$(NAME):
	cd philo && make && cd ..

$(BNAME):
	cd philo_bonus && make && cd ..

clean: $(OBJS)
	rm -f $(OBJS)

fclean: clean $(LIBS)
	rm -f $(NAME) $(BNAME) $(LIBS)

re: clean fclean all

rebonus: clean fclean bonus

autogit: fclean
	git status
	git add *
	git status
	echo "\nPlease, enter your commit message:"
	read commit_message; git commit -m "$$commit_message"
	git status
	git push


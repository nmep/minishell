# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 18:47:20 by picatrai          #+#    #+#              #
#    Updated: 2024/03/14 02:21:53 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCDIR = src
OBJDIR = obj
SRC =  $(shell find $(SRCDIR) -type f -name '*.c')
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INCLUDE = -I include
header = ./include/minishell.h
dir_in_src = $(notdir $(shell find ./src/* -type d))


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(header) | obj_dir_create
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE)

all: $(NAME)

$(NAME):  $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(RFLAGS)

obj_dir_create:
	@if [ ! -d "./obj" ]; then\
		mkdir -p obj;\
	fi;\
	for d in $(dir_in_src); do\
		if [ ! -d ./obj/$$d ]; then\
			mkdir -p ./obj/$$d/;\
		fi;\
	done;\

clean:
	rm -rf $(OBJ) ./obj

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean obj_dir_create

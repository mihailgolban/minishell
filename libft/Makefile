# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/07 02:00:01 by mgolban           #+#    #+#              #
#    Updated: 2017/02/14 23:20:43 by mgolban          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The name of binary file
NAME = libft.a
# The compiler to use:
CC = gcc
# Compiler flags for release:
CFLAGS = -Wall -Wextra -Werror
# Command to remove files and directories
RM	= /bin/rm -rf
# Sources
SOURCES = $(wildcard *.c)
# Objects
OBJECTS = $(SOURCES:.c=.o)

# Default make
all	: $(NAME)

# Build Object Files
%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(CC) $(CFLAGS) -c -o $< \\033[1;32m >> \\033[0;39m $@ \\033[1;32m OK \\033[0;39m"

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

# Fast cleaning
.PHONY: clean
clean :
	@$(RM) $(OBJECTS)
	@echo "\\033[1;31mDELETING >> \\033[0;39m libft/*.o"

# Advanced cleaning
.PHONY: fclean
fclean : clean
	@$(RM) $(NAME)
	@echo "\\033[1;31mDELETING >> LIBRARY \\033[0;39m $(NAME)"

# Rebuild project
.PHONY: re
re : fclean all

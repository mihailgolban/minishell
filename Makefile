# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgolban <mgolban@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/01 01:19:53 by mgolban           #+#    #+#              #
#    Updated: 2017/02/14 23:20:27 by mgolban          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The name of binary file
RELEASE_BIN = minishell
# Library directory (leave empty if there is not library)
LIB_DIR = libft
# The compiler to use:
CC = gcc
# Compiler flags for release:
CFLAGS = -Wall -Wextra -Werror -I $(LIB_DIR)
# Linking flag for release
LFLAGS = -L $(LIB_DIR) -lft
# Flag for debug:
DEBUG = -g3
# Command to remove files and directories
RM	= /bin/rm -rf
# Argument for makefile library
LIB_FLAG = clean

# Sources dir with "/" (leave empty for current directory)
SRC_DIR = src/
SOURCES = $(wildcard $(SRC_DIR)*.c)

# Objects dir with "/" (leave empty for current directory)
OBJ_DIR = obj/
OBJECTS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SOURCES))

# Default make
all	: $(OBJ_DIR) $(RELEASE_BIN)

$(OBJ_DIR) :
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)

# Build Object Files
$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(DEBUG) -c -o $@ $<
	@echo "$(CC) $(CFLAGS) $(DEBUG) -c -o $< \\033[1;32m >> \\033[0;39m $@ \\033[1;32m OK \\033[0;39m"

# Build Release
$(RELEASE_BIN) : $(OBJECTS) 
ifdef LIB_DIR
	@make -C $(LIB_DIR)
endif
	$(CC) -o $(RELEASE_BIN) $(OBJECTS) $(LFLAGS)
	@echo "\\033[1;33m-----------COMPILATION FINISHED----------- \\033[0;39m"

# Fast cleaning
.PHONY: clean
clean :

ifdef LIB_DIR
	@make -C $(LIB_DIR) $(LIB_FLAG)
endif
	@$(RM) $(OBJECTS)
	@echo "\\033[1;31mDELETING >> \\033[0;39mobj/*.o"

# Advanced cleaning
.PHONY: fclean
fclean : LIB_FLAG = fclean
fclean : clean
	@$(RM) $(RELEASE_BIN)
	@echo "\\033[1;31mDELETING >> BINARY \\033[0;39m $(RELEASE_BIN)"

# Rebuild project
.PHONY: re
re : fclean all

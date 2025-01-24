# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 18:54:13 by llebugle          #+#    #+#              #
#    Updated: 2025/01/22 18:43:51 by maxweert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program file name
NAME	= minishell

# -----------------------------------Colors------------------------------------

RED		=\033[0;31m
GREEN	=\033[0;32m
YELLOW	=\033[1;33m
BLUE	=\033[0;34m
ORANGE	=\033[38;2;255;165;0m
RESET	=\033[0m

# Compiler and compilation flags
CC		= cc
# CFLAGS	= -Werror -Wextra -Wall -gdwarf-4 -g
CFLAGS	=
VALGRIND =

ifeq ($(MODE), debug)
	CFLAGS	+= -fsanitize=address -gdwarf-4 -g
else ifeq ($(MODE), valgrind)
	VALGRIND += valgrind --leak-check=full --show-leak-kinds=all --suppressions=leaks.supp
endif 

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

SRC		= 	main.c \
			tokenizer/token_handlers.c \
			tokenizer/tokenizer.c \
			tokenizer/utils.c \
			tokenizer/debug.c \
			builtins/env.c \
			builtins/pwd.c \
			builtins/unset.c \
			builtins/export.c \
			builtins/echo.c \
			misc/signal.c \
			misc/expander.c \
			misc/expander_utils.c \
			misc/env_utils.c \
			misc/env_utils2.c

OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

# Libft files and directories
LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

# Main rule
all: $(OBJ_PATH) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/tokenizer
	mkdir -p $(OBJ_PATH)/misc
	mkdir -p $(OBJ_PATH)/builtins
# mkdir -p $(OBJ_PATH)/utils

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -l readline

# Libft rule
$(LIBFT):
	make -C $(LIBFT_PATH)

# Clean up build files rule
clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

# Remove program executable
fclean: clean
	rm -f $(NAME)
	rm -rf $(TESTER_DIR)
	make -C $(LIBFT_PATH) fclean

# Clean + remove executable
re: fclean all

# Testing rule
TEST_NAME = lexer
TESTER_DIR = testers
TEST_OBJ = $(TEST_SRC:.c=.o)

lexer: $(OBJ_PATH) $(filter-out $(OBJ_PATH)main.o, $(OBJS)) 
	mkdir -p $(OBJ_PATH)/testing
	mkdir -p $(TESTER_DIR)
	$(CC) $(CFLAGS) -c srcs/tests/test_tokenizer.c -o $(OBJ_PATH)/testing/test_tokenizer.o $(INC)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_PATH)main.o, $(OBJS)) $(OBJ_PATH)/testing/test_tokenizer.o -o $(TESTER_DIR)/lexer $(INC) $(LIBFT) -l readline
	@echo "$(BLUE)lexer program compiled successfully!$(RESET)"
	@$(TESTER_DIR)/lexer
	
expander: $(OBJ_PATH) $(filter-out $(OBJ_PATH)main.o, $(OBJS))
	mkdir -p $(TESTER_DIR)
	mkdir -p $(OBJ_PATH)/testing
	$(CC) $(CFLAGS) -c srcs/tests/test_expander.c -o $(OBJ_PATH)testing/test_expander.o $(INC)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_PATH)main.o, $(OBJS)) $(OBJ_PATH)/testing/test_expander.o -o $(TESTER_DIR)/expander $(INC) $(LIBFT) -l readline
	@echo "$(BLUE)expander program compiled successfully!$(RESET)"
	$(if $(VALGRIND), $(VALGRIND)) $(TESTER_DIR)/expander

.PHONY: all re clean fclean test lexer expander
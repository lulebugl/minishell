# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 18:54:13 by llebugle          #+#    #+#              #
#    Updated: 2025/01/22 03:34:08 by maxweert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program file name
NAME	= minishell

# Compiler and compilation flags
CC		= cc
# CFLAGS	= -Werror -Wextra -Wall -gdwarf-4 -g
CFLAGS	=

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
			misc/signal.c \
			misc/env.c \
			misc/utils.c

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
	make -C $(LIBFT_PATH) fclean

# Clean + remove executable
re: fclean all

# Testing rule
TEST_NAME = lexer
TEST_SRC = srcs/tokenizer/test_tokenizer.c
TEST_OBJ = $(TEST_SRC:.c=.o)

lexer: $(OBJ_PATH) $(filter-out $(OBJ_PATH)main.o, $(OBJS))
	mkdir -p $(OBJ_PATH)/testing
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o $(OBJ_PATH)/testing/test_lexer.o $(INC)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_PATH)main.o, $(OBJS)) $(OBJ_PATH)/testing/test_lexer.o -o $(TEST_NAME) $(INC) $(LIBFT) -l readline
	@echo "Test program compiled successfully!"
	@./$(TEST_NAME)

.PHONY: all re clean fclean test lexer
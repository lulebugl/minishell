# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 18:54:13 by llebugle          #+#    #+#              #
#    Updated: 2025/02/19 16:26:14 by maxweert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
CFLAGS	= -Wextra -Wall -gdwarf-4 -g
VALGRIND =

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS
    READLINE_LIB := -L/usr/local/opt/readline/lib
    READLINE_INC := -I/usr/local/opt/readline/include
    CFLAGS	+= -I/usr/local/opt/readline/include
    
else
    READLINE_LIB := -lreadline
    READLINE_INC :=
    
endif

ifeq ($(MODE), debug)
	CFLAGS	+= -fsanitize=address -gdwarf-4 -g -D DEBUG=true
else ifeq ($(MODE), valgrind)
	VALGRIND += valgrind --leak-check=full --show-leak-kinds=all --suppressions=leaks.supp
endif 

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

SRC		= 	main.c \
			tokenizer/token_utils.c \
			tokenizer/token_handlers.c \
			tokenizer/tokenizer.c \
			tokenizer/validate_prompt.c \
			tokenizer/debug.c \
			builtins/env.c \
			builtins/pwd.c \
			builtins/unset.c \
			builtins/export.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/cd.c \
			misc/signal.c \
			misc/error.c \
			misc/env_utils.c \
			misc/env_utils2.c \
			misc/free.c \
			misc/init.c \
			parsing/ast_debug.c \
			parsing/command.c \
			parsing/redirections.c \
			parsing/wildcards.c \
			parsing/tree.c \
			parsing/parser.c	\
			parsing/heredoc.c \
			exec/debug.c \
			exec/exec.c \
			exec/utils.c \
			exec/process.c \
			exec/expander.c \
			exec/expander_utils.c \
			exec/path.c
		 

OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

# Libft files and directories
LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

# Main rule
all: $(OBJ_PATH) $(LIBFT) $(NAME)
	
run : all
	@./$(NAME)
	
# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/tokenizer
	mkdir -p $(OBJ_PATH)/misc
	mkdir -p $(OBJ_PATH)/builtins
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/exec

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
# $(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -l readline
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(READLINE_LIB) $(READLINE_INC) -l readline

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

ast: $(OBJ_PATH) $(filter-out $(OBJ_PATH)main.o, $(OBJS))
	mkdir -p $(TESTER_DIR)
	mkdir -p $(OBJ_PATH)/testing
	$(CC) $(CFLAGS) -c srcs/tests/test_ast.c -o $(OBJ_PATH)testing/test_ast.o $(INC)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_PATH)main.o, $(OBJS)) $(OBJ_PATH)/testing/test_ast.o -o $(TESTER_DIR)/ast $(INC) $(LIBFT) -l readline
	@echo "$(BLUE)ast program compiled successfully!$(RESET)"
	$(if $(VALGRIND), $(VALGRIND)) $(TESTER_DIR)/ast
	
exec: $(OBJ_PATH) $(filter-out $(OBJ_PATH)main.o, $(OBJS))
	mkdir -p $(TESTER_DIR)
	mkdir -p $(OBJ_PATH)/testing
	$(CC) $(CFLAGS) -c srcs/tests/test_exec.c -o $(OBJ_PATH)testing/test_exec.o $(INC)
	$(CC) $(CFLAGS) $(filter-out $(OBJ_PATH)main.o, $(OBJS)) $(OBJ_PATH)/testing/test_exec.o -o $(TESTER_DIR)/exec $(INC) $(LIBFT) $(READLINE_LIB) $(READLINE_INC) -l readline
	@echo "$(BLUE)exec program compiled successfully!$(RESET)"
	$(if $(VALGRIND), $(VALGRIND)) $(TESTER_DIR)/exec

.PHONY: all re clean fclean run test lexer expander ast
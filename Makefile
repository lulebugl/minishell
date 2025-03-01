# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxweert <maxweert@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 18:54:13 by llebugle          #+#    #+#              #
#    Updated: 2025/02/27 21:25:34 by llebugle         ###   ########.fr        #
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
CFLAGS	= -Werror -Wextra -Wall -gdwarf-4 -g
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
			tokenizer/checkers.c \
			tokenizer/tokenizer.c \
			tokenizer/token_handlers.c \
			tokenizer/token_utils.c \
			tokenizer/extend_prompt.c \
			tokenizer/validate_prompt.c \
			builtins/env.c \
			builtins/pwd.c \
			builtins/unset.c \
			builtins/export.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/cd.c \
			expander/expander.c \
			expander/expand_tilde.c \
			expander/expand_keys.c \
			expander/expander_utils.c \
			expander/split_expanded.c \
			expander/expand_wildcards.c \
			expander/expand_wildcards_utils.c \
			expander/quotes.c \
			misc/signal.c \
			misc/prompt.c \
			misc/prompt_git.c \
			misc/error.c \
			misc/utils.c \
			misc/env_utils.c \
			misc/env_utils2.c \
			misc/free.c \
			misc/init.c \
			parsing/command.c \
			parsing/redirections.c \
			parsing/tree.c \
			parsing/tree_utils.c \
			parsing/heredoc.c \
			parsing/heredoc_utils.c \
			exec/exec.c \
			exec/exec_builtin.c \
			exec/utils.c \
			exec/process.c \
			exec/redirect.c \
			exec/path.c \
			debug/debug_ast.c \
			debug/debug_exec.c \
			debug/debug_tokenizer.c \


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

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/tokenizer
	mkdir -p $(OBJ_PATH)/misc
	mkdir -p $(OBJ_PATH)/builtins
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/exec
	mkdir -p $(OBJ_PATH)/expander
	mkdir -p $(OBJ_PATH)/debug

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(READLINE_LIB) $(READLINE_INC) -l readline

# Libft rule
$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(TESTER_DIR)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all re clean fclean run 

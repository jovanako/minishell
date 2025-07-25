# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/07 17:02:03 by jkovacev          #+#    #+#              #
#    Updated: 2025/07/25 19:31:10 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------------------------#
#---------------------DEFINES-----------------------#
#---------------------------------------------------#

NAME = minishell

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

INC = -Llibft -lft -lreadline

#---------------------------------------------------#
#---------------------SOURCES-----------------------#
#---------------------------------------------------#

BUILTINS = cd echo env exit export export_helpers pwd signals unset

ENV = env_vars add_env_var get_env_var

EXEC = execution execution_execve execution_built_in execution_helpers execution_no_command open_fork_stream cmdpath

EXPANSION = expansion expansion_helpers slicing

MAIN = main

PARSING = parsing parsing_helpers parsing_assignment parsing_redirection parsing_argv parsing_callbacks

TOKENIZER = tokenizer tokenizer_helper token_readers heredoc_reader

UTILS = call_backs strings		

SRC = $(addsuffix .c, $(addprefix built-ins/, $(BUILTINS))) \
	  $(addsuffix .c, $(addprefix env_vars/, $(ENV))) \
	  $(addsuffix .c, $(addprefix execution/, $(EXEC))) \
	  $(addsuffix .c, $(addprefix expansion/, $(EXPANSION))) \
	  $(addsuffix .c, $(addprefix parsing/, $(PARSING))) \
	  $(addsuffix .c, $(addprefix tokenizer/, $(TOKENIZER))) \
	  $(addsuffix .c, $(addprefix utils/, $(UTILS))) \
	  $(addsuffix .c, $(MAIN)) \

OBJ = $(SRC:c=o)

#---------------------------------------------------#
#----------------------RULES------------------------#
#---------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@make -C libft/ bonus
	@echo "\033[0;32mCompiling..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC)
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nRemoving objects..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@make clean
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re
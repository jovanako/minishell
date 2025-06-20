# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/07 17:02:03 by jkovacev          #+#    #+#              #
#    Updated: 2025/06/20 20:28:48 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c \
		tokenizer.c \
		tokenizer_helper.c \
		token_readers.c \
		heredoc_reader.c \
		env_vars.c \
		expansion.c \
		expansion_helpers.c \
		call_backs.c

OBJDIR = objects
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME) : libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -lreadline -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

libft:
	$(MAKE) -C libft bonus

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C libft fclean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft

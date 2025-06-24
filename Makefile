# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/07 17:02:03 by jkovacev          #+#    #+#              #
#    Updated: 2025/06/24 09:57:46 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = minishell.a

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

SRCS = main.c \
		tokenizer/tokenizer.c \
		tokenizer/tokenizer_helper.c \
		tokenizer/token_readers.c \
		tokenizer/heredoc_reader.c \
		env_vars.c \
		expansion.c \
		expansion_helpers.c \
		slicing.c \
		call_backs.c

OBJDIR = objects
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME) $(LIB)

$(NAME) : libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -lreadline -o $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $@/tokenizer $@/expansion	
#move to minishell_tests
$(LIB): $(filter-out $(OBJDIR)/main.o, $(OBJS))
	ar rcs $@ $^

libft:
	$(MAKE) -C libft bonus

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C libft fclean

fclean: clean
	rm -f $(NAME) $(LIB)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft package

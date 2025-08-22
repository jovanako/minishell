# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 11:46:37 by jkovacev          #+#    #+#              #
#    Updated: 2025/08/22 20:23:23 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = liberrprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

DEPS = err_printf.h

SRCS = err_printf.c \
	 arg_conversions/print_char.c \
	 arg_conversions/print_string.c \
	 arg_conversions/print_pointer.c \
	 arg_conversions/print_int.c \
	 arg_conversions/print_unsigned.c \
	 arg_conversions/print_hex_low.c \
	 arg_conversions/print_hex_up.c \
	 helpers/write_str.c \
	 helpers/print_hexadecimal.c \
	 helpers/err_putstr.c \
	 helpers/is_valid_format_string.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

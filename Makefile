# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsorion <tsorion@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:20:15 by mphobos           #+#    #+#              #
#    Updated: 2020/01/27 16:47:40 by tsorion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CREADLINE = readline.c quoting.c
READLINE = $(patsubst %,src/readline/%,$(CREADLINE))
CC = gcc
INCLUDE = includes
CFLAGS = -L libft -lft -ltermcap -I $(INCLUDE) -o $(NAME)
DFLAGS = $(CFLAGS) -g

%.c:
	$(CC) src/main.c $(READLINE) $(DFLAGS) -c $<

$(NAME): src/main.c $(READLINE)
	make -C libft
	$(CC) src/main.c $(READLINE) $(DFLAGS)

all: $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

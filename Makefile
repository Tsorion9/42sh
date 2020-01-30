# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:20:15 by mphobos           #+#    #+#              #
#    Updated: 2020/01/30 13:38:03 by mphobos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CREADLINE = readline.c user_in_editing.c cursor_manipulation.c
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

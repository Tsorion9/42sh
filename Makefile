# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsorion <tsorion@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:20:15 by mphobos           #+#    #+#              #
#    Updated: 2020/04/12 21:53:18 by tsorion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CREADLINE = readline.c user_in_editing.c cursor_manipulation.c expansion.c \
			termcap_api.c ft_isspace.c history_list.c \
			delete.c history_file.c free.c
CTOKENIZING = get_next_token.c
READLINE = $(patsubst %,src/readline/%,$(CREADLINE))
TOKENIZING = $(patsubst %,src/tokenizing/%,$(CTOKENIZING))
CC = gcc
INCLUDE = includes 
LIB_INC = libft/includes
CFLAGS = -Wall -Wextra -L libft -lft -ltermcap -I $(INCLUDE) -I $(LIB_INC) -o $(NAME)
DFLAGS = $(CFLAGS) -g

%.c:
	$(CC) src/main.c $(READLINE) $(TOKENIZING) $(DFLAGS) -c $<

$(NAME): src/main.c $(READLINE) $(TOKENIZING)
	make -C libft
	$(CC) src/main.c $(READLINE) $(TOKENIZING) $(DFLAGS)

all: $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

val:
	valgrind --leak-check=full ./21sh

.PHONY: all clean fclean re

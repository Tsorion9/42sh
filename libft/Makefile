# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsorion <tsorion@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:04:53 by mphobos           #+#    #+#              #
#    Updated: 2020/01/27 16:42:44 by tsorion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	  ft_strcat.c ft_strncat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	  ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
	  ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
	  ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
	  ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	  ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	  ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c \
	  ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	  ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	  ft_lstiter.c ft_lstmap.c ft_memmove.c ft_strlcat.c get_next_line.c \
	  ft_freestrsplit.c \
	ftoa/decimal_arithmetic2.c\
	ftoa/decimal_arithmetic3.c\
	ftoa/decimal_arithmetic4.c\
	ftoa/decimal_arithmetic5.c\
	ftoa/decimal_arithmetic.c\
	ftoa/ftoa2.c\
	ftoa/ftoa.c\
	ft_printf/apply_spec2.c\
	ft_printf/apply_spec3.c\
	ft_printf/apply_spec4.c\
	ft_printf/apply_spec5.c\
	ft_printf/apply_spec6.c\
	ft_printf/apply_spec.c\
	ft_printf/arg_extractors2.c\
	ft_printf/arg_extractors.c\
	ft_printf/conv_int2.c\
	ft_printf/conv_int.c\
	ft_printf/conv_other.c\
	ft_printf/conv_wrappers_int2.c\
	ft_printf/conv_wrappers_int.c\
	ft_printf/conv_wrappers_other.c\
	ft_printf/find_action.c\
	ft_printf/fprintf.c\
	ft_printf/printf.c\
	ft_printf/read_spec2.c\
	ft_printf/read_spec.c\
	ft_itoa_base.c\
	ft_strrev.c\
	ft_ptree_to_kvpairs.c\
	ft_ptree.c\
	ft_path_append.c\
	ft_copy_ptree.c\
	ft_straddchar.c\
	ft_lstlen.c\
	ft_lstnew_inplace.c\
	get_next_line_wrapper.c\
	xmalloc.c


OBJ = $(patsubst %.c,%.o,$(SRC))
CC = gcc
INCLUDE = includes
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE) -I ft_printf -I ftoa
DFLAGS = $(CFLAGS) -g

%.o: %.c
	$(CC) $(DFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

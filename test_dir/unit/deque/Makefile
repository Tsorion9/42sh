LIBFT = "../../libft"
INC="../../libft/includes"

all: re test_deque

re:
	rm -f test_deque test_2list

test_2list:
	gcc -g -Wall -Wextra t2list.c test_2list.c -I . -I $(LIBFT) -L $(LIBFT) -lft -o test_2list

test_deque:
	gcc -g -Wall -Wextra t2list.c deque.c deque_len.c test_deque.c -I . -I $(INC) -L $(LIBFT) -lft -o test_deque

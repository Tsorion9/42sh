NAME =  ftoa.o

define SRC 
ftoa.c ftoa2.c decimal_arithmetic.c decimal_arithmetic2.c decimal_arithmetic3.c decimal_arithmetic4.c decimal_arithmetic5.c

endef

$(NAME):
	@echo "Compiling Ftoa files"
	@gcc -g -Wall -Wextra -Werror -I . -c $(SRC) 

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean

re: fclean all
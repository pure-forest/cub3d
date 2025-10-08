NAME := print_error_test

SRC := \
	   ../../src/errors/errors.c \
	   print_error_test.c

LIBFT := ../../libft/libft.a

all: $(NAME)

$(LIBFT): phony
	(cd ../../libft && make)

$(NAME): $(LIBFT) $(SRC)
	cc -Wall -Wextra -Werror $(SRC) $(LIBFT) -o $(NAME)

clean:
	(cd ../../libft && make clean)

fclean: clean
	(cd ../../libft && make fclean)
	rm -rf $(NAME)

re: fclean all

.PHONY: all phony clean fclean re

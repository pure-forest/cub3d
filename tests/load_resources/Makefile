NAME := load_resources_test

SRC := \
	   ../../src/load_map/errors.c \
	   ../../src/load_map/load_resources.c \
	   ../../src/load_map/map_data.c \
	   ../../src/load_map/map_data_utils.c \
	   ../../src/load_map/map_utils.c \
	   ../../src/color/color.c \
	   load_resources_test.c

LIBFT := ../../libft/libft.a

MLX42_DIR := ../../MLX42/
MLX42 := ../../MLX42/build/libmlx42.a
MLX42_FLAGS := -Iinclude -ldl -lglfw -pthread -lm

all: $(MLX42) $(LIBFT) $(NAME)

test: all
	./$(NAME)

$(MLX42): $(MLX42_DIR)
	cd ../../MLX42 && cmake -B build && cmake --build build -j4

$(MLX42_DIR):
	cd ../../ && git clone https://github.com/codam-coding-college/MLX42.git

$(LIBFT): phony
	(cd ../../libft && make)

$(NAME): $(SRC)
	cc -Wall -Wextra -Werror $(SRC) $(LIBFT) $(MLX42) $(MLX42_FLAGS) -g -o $(NAME)

clean:
	(cd ../../libft && make clean)

fclean: clean
	(cd ../../libft && make fclean)
	rm -rf $(NAME)

re: fclean all

.PHONY: all phony clean fclean re

NAME := image_to_image_test

SRC := \
	   ../../src/minimap/rect.c \
	   ../../src/minimap/image_to_image.c \
	   ../../src/color/color.c \
	   img_to_img_test.c

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

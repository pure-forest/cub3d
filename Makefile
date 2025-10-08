#
#			  \\\\\\   \\\    \\\  \\\\\\\\     \\\\\\    \\\\\\\\
#			 \\######  \###   \### \########   \\######   \########
#			\\##   \## \###   \### \###\\\###  \##  \###  \###  \###
#			\###   \## \###   \### \#########      \\\### \###   \###
#			\###       \###   \### \###   \###     \####  \###   \###
#			\###   \\  \###  \\### \###   \\## \\   \\### \###  \\###
#			 \##\\\\##  \###\\###  \###\\\\### \##\\\###  \###\\\###
#			  \######    \######   \#########   \######   \########
#

#####  FILES  ##################################################################

NAME := ./bin/cub3d

SRC_DIR := ./src/

COLOR := \
		color.c
DRAW := \
		draw.c \
		draw_line.c \
		rect.c \
		image_to_image.c
ERRORS := \
		errors.c
GAME := \
		game_cleanup.c \
		game_init.c
HOOKS := \
		close_hook.c \
		cursor_hook.c \
		loop_hook.c
INPUT := \
		 input.c
LOAD_MAP := \
		error_map_file_incomplete.c \
		load_assets.c \
		load_map.c \
		map_utils.c \
		map_validation.c \
		parse_assets.c \
		parse_grid.c
MINIMAP := \
		get_map_image.c \
		update_minimap.c
PLAYER_MOVEMENT := \
		player_movement.c \
		collision.c
RAYCASTING := \
		cast_ray.c \
		raycasting.c
RENDER:= \
		render_floor_and_ceiling.c \
		render_walls.c
VEC2 := \
		vec2.c
MAIN := \
		main.c \

SRC := $(addprefix $(SRC_DIR)color/, $(COLOR)) \
	   $(addprefix $(SRC_DIR)draw/, $(DRAW)) \
	   $(addprefix $(SRC_DIR)errors/, $(ERRORS)) \
	   $(addprefix $(SRC_DIR)game/, $(GAME)) \
	   $(addprefix $(SRC_DIR)hooks/, $(HOOKS)) \
	   $(addprefix $(SRC_DIR)input/, $(INPUT)) \
	   $(addprefix $(SRC_DIR)load_map/, $(LOAD_MAP)) \
	   $(addprefix $(SRC_DIR)minimap/, $(MINIMAP)) \
	   $(addprefix $(SRC_DIR)player_movement/, $(PLAYER_MOVEMENT)) \
	   $(addprefix $(SRC_DIR)raycasting/, $(RAYCASTING)) \
	   $(addprefix $(SRC_DIR)render/, $(RENDER)) \
	   $(addprefix $(SRC_DIR)vec2/, $(VEC2)) \
	   $(addprefix $(SRC_DIR), $(MAIN))

OBJ_DIR := ./obj/
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

INC := \
	   color.h \
	   defs.h \
	   draw.h \
	   errors.h \
	   game.h \
	   hooks.h \
	   input.h \
	   map.h \
	   minimap.h \
	   player_movement.h \
	   raycasting.h \
	   vec2.h

INC_DIR := ./inc/
INC := $(addprefix $(INC_DIR), $(INC))

DEBUG := ./debug/cub3d

#LIBFT- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
LIBFT := ./libft/libft.a

#MLX42- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
MLX42 := ./MLX42/build/libmlx42.a
MLX42_DIR := ./MLX42/
MLX42_FLAGS := -Iinclude -ldl -lglfw -pthread -lm

#HOOKS- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
HOOKS := ./.git/hooks/pre-commit

#####  COMPILERS  ##############################################################

CC := cc
CFLAGS := -Wall -Wextra -Werror -Ofast

#####  RULES  ##################################################################

all: $(HOOKS) $(MLX42) $(NAME)

$(HOOKS): ./.githooks/pre-commit
	@sh ./install-hooks.sh

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLX42_FLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p obj
	@mkdir -p obj/load_map
	@mkdir -p obj/errors
	@mkdir -p obj/color

#LIBFT- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
$(LIBFT): phony
	@(cd libft && make CFLAGS="$(CFLAGS)")

#MLX42- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
$(MLX42): $(MLX42_DIR)
	cd MLX42 && cmake -B build && cmake --build build -j4

$(MLX42_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git


#CLEANUP------------------------------------------------------------------------
clean:
	@rm -rf $(OBJ_DIR)
	@(cd libft && make clean)

fclean: clean
	@rm -rf $(NAME) .mlxcloned ./MLX42
	@(cd libft && make fclean)
	@rm -rf bin
	@rm -rf debug

re: fclean all

#DEBUG--------------------------------------------------------------------------
debug: CFLAGS := -Wall -Wextra -Werror -g
debug: clean $(MLX42) $(DEBUG)

$(DEBUG): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@mkdir -p debug
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42) $(MLX42_FLAGS) -o $@
	@make clean

.PHONY: all clean fclean re debug phony

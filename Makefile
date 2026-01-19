NAME := cub3d
CC := cc
CFLAGS := -Wall -Werror -Wextra -g
LFLAGS := -

MLX_REPO := https://github.com/42paris/minilibx-linux
MLX_PATH := ./mlx
MLX := $(MLX_PATH)/libmlx_Linux.a -lXext -lX11 -lm -lz

SRC := \
	   main.c \
	   init_data.c \
	   hook_events.c \
	   clean_up.c \
	   game_loop.c \
	   render_frame.c \
	   utils/deg_to_rad.c \
	   utils/create_rgb.c \
	   utils/get_time_ms.c \
	   my_mlx/my_mlx_pixel_put.c \
	   my_mlx/my_mlx_create_image.c \
	   my_mlx/my_mlx_get_pixel_color.c \
	   movement/move_player.c \
	   movement/check_collision.c \
	   movement/move_backward.c \
	   movement/move_forward.c \
	   movement/move_left.c \
	   movement/move_right.c \
	   movement/rotate_left.c \
	   movement/rotate_right.c \
	   raycasting/shoot_ray.c \
	   raycasting/draw_textured_line.c \
	   raycasting/detect_wall.c \
	   raycasting/draw_walls.c \
	   raycasting/finalize_ray.c \
	   raycasting/find_gridline.c \
	   raycasting/out_of_bounds.c \
	   parser/parser.c \
	   parser/parser_validate_map.c \
	   parser/parser_misc_utils.c \
	   parser/parser_string_utils.c \
	   parser/parser_map_utils.c \
	   parser/parser_metadata.c \
	   parser/parser_map.c \
	   parser/parser_file_reader.c \
	   parser/convert_map_to_level.c

OBJ = $(addprefix obj/, $(SRC:.c=.o))

all : $(NAME)

$(MLX):
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "Downloading MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_PATH); \
	fi
	@echo "Compiling MiniLibX..."
	@make -C $(MLX_PATH)

obj/%.o : src/%.c 
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(MLX) $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME) 

clean :
	rm -rf obj
	rm -rf $(MLX_PATH)

fclean : clean
	rm -rf $(NAME)

re : fclean
	$(MAKE) all

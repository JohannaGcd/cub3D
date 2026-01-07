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
	   deg_to_rad.c \
	   render_frame.c \
	   test/test_image.c \
	   test/mock_parser.c \
	   my_mlx/my_mlx_pixel_put.c \
	   my_mlx/my_mlx_create_image.c \
	   my_mlx/my_mlx_get_pixel_color.c \
	   raycasting/shoot_ray.c \
	   raycasting/draw_textured_line.c \
	   raycasting/detect_wall.c \
	   raycasting/finalize_ray.c \
	   raycasting/find_gridline.c \
	   raycasting/out_of_bounds.c 

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
	rm -rf $(OBJ)
	rm -rf $(MLX_PATH)

fclean : clean
	rm -rf $(NAME)

re : fclean
	$(MAKE) all

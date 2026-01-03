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
	   mock_parser.c \
	   hook_events.c

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

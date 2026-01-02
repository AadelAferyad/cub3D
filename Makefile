NAME = cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -I includes
LFLAGS = -lmlx -lX11 -lXext -lm
SOURCE = main.c dda.c textures_mlx.c vector2d.c minimap.c destory_game.c draw_func.c keys.c gnl/get_next_line.c gnl/get_next_line_utils.c parse/parse.c parse/file_valid.c parse/config_valid.c parse/utils.c parse/map_valid.c
OBJ = $(SOURCE:.c=.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

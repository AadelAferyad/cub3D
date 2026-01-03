NAME = cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -I includes
LFLAGS = -lmlx -lX11 -lXext -lm
SOURCE = src/main.c src/dda.c src/textures_mlx.c src/vector2d.c src/vector2d_advance.c src/minimap.c src/destory_game.c src/draw_func.c src/keys.c gnl/get_next_line.c gnl/get_next_line_utils.c src/parse/file_valid.c src/parse/parser.c src/parse/config_valid.c src/parse/utils.c src/parse/map_valid.c src/parse/map_checks.c src/parse/config_checks.c src/parse/parse_utils.c src/parse/memory_utils.c
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

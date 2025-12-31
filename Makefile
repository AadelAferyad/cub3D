NAME = cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -I includes -lmlx -lX11 -lXext -lm
SOURCE = main.c gnl/get_next_line.c gnl/get_next_line_utils.c parse/parse.c 
OBJ = $(SOURCE:.c=.o)
LIBFT = make -C libft
# cc main.c draw_map.c dda.c parse/parse.c libft/libft.a gnl/get_next_line_utils.c gnl/get_next_line.c vector2d.c textures_mlx.c minimap.c -I includes -lmlx -lX11 -lXext -lm V

all: $(NAME)
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(FLAGS) $(LIBFT) -o $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	make fclean -C libft
	rm -rf cub3d 

re: fclean all

NAME = cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -I includes -lmlx -lX11 -lXext -lm
SOURCE = main.c gnl/get_next_line.c gnl/get_next_line_utils.c parse/parse.c 
OBJ = $(SOURCE:.c=.o)
LIBFT = make -C libft
 cc main.c draw_map.c dda.c -I includes -lmlx -lX11 -lXext -lm parse/parse.c libft/libft.a gnl/get_next_line_utils.c gnl/get_next_line.c

all: $(NAME)


$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)
clean:
	rm -f $(OBJ)
fclean: clean
	make fclean -C libft
	rm -rf cub3d 

re: fclean all

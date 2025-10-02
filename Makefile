NAME = cub3d
CC = cc
FLAGS = -Werror -Wextra -Wall -I includes -lmlx -lX11 -lXext -lm



all: $(NAME)

# $(LIBFT) :
# 	make -C libft

$(NAME):
	make -C libft
	$(CC) main.c gnl/get_next_line.c gnl/get_next_line_utils.c parse/parse.c $(FLAGS) libft/libft.a -o $(NAME)
fclean:
	rm -rf cub3d

NAME = cub3d
CC = cc
FLAGS = -Werror -Wextra -Wall -I includes -lmlx -lX11 -lXext 



all: $(NAME)

# $(LIBFT) :
# 	make -C libft

$(NAME):
	make -C libft
	$(CC) main.c parse/parse.c  $(FLAGS) libft/libft.a -o $(NAME)

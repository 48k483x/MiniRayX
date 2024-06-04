NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c vector.c ray.c lighting.c
OBJS = $(SRCS:.c=.o)

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

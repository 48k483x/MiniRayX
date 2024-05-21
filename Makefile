FLAGS = -Wall -Wextra -Werror
MLXFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
SRC = main.c
NAME = prog
			

OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME) -lreadline

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
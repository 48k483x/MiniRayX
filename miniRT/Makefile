FLAGS = -g -Wall -Wextra -Werror 

SRC = 	 mandatory/main.c mandatory/allocation.c  \
         mandatory/split.c mandatory/vector.c mandatory/normal_vector.c \
         mandatory/vector2.c mandatory/ray_tracing.c  \
         mandatory/intersection.c mandatory/tools.c  \
         mandatory/mlx_func.c mandatory/camera.c mandatory/color.c \
         mandatory/surface_normale.c mandatory/world.c mandatory/libft_2.c \
         mandatory/shading.c mandatory/gnl.c mandatory/gnl_utils.c \
         mandatory/select.c mandatory/select_2.c mandatory/acl.c \
         mandatory/spcypl.c mandatory/libft.c mandatory/get_scene.c \
         

NAME = miniRT
OBJ = $(SRC:.c=.o)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    OS_FLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
else ifeq ($(UNAME_S), Darwin)
    OS_FLAGS = -lmlx -framework OpenGL -framework AppKit
else
    $(error Unsupported operating system)
endif

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(FLAGS) $(OBJ) $(OS_FLAGS) -o $(NAME)

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

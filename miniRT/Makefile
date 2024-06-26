FLAGS = -g

SRC = miniRT.c \
	srcs/gnl/gnl.c srcs/gnl/gnl_utils.c \
	srcs/utils/libft.c srcs/utils/split.c \
	srcs/utils/error.c \
	srcs/parsing/print_scene.c \
	srcs/parsing/acl.c srcs/parsing/select.c srcs/parsing/sp_pl_cy.c srcs/parsing/get_scene.c\
	srcs/ray_gen/vector.c \
	srcs/raytrace/camera.c srcs/raytrace/raytrace.c srcs/raytrace/intersection.c

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

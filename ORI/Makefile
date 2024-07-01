HEADER = includes/minirt.h

NAME = miniRT
NAME_B = miniRT_bonus

M_SRCS = mandatory/main.c mandatory/allocation.c \
         mandatory/tools.c \
         mandatory/split.c mandatory/vector.c mandatory/normal_vector.c \
         mandatory/vector2.c mandatory/ray_tracing.c  \
         mandatory/Garbage_Collector.c mandatory/intersection.c \
         mandatory/mlx_func.c mandatory/camera.c mandatory/color.c \
         mandatory/surface_normale.c mandatory/world.c mandatory/split_utils.c \
         mandatory/shading.c mandatory/gnl.c mandatory/gnl_utils.c \
         mandatory/select.c mandatory/select_2.c mandatory/acl.c \
         mandatory/spcypl.c mandatory/libft.c mandatory/get_scene.c

B_SRCS = bonus/main.c bonus/get_next_line.c bonus/allocation.c \
         bonus/tools.c bonus/parse_element.c bonus/parse.c \
         bonus/split.c bonus/vector.c bonus/normal_vector.c \
         bonus/vector2.c bonus/ray_tracing.c bonus/parse_objects.c \
         bonus/Garbage_Collector.c bonus/intersection.c \
         bonus/mlx_func.c bonus/camera.c bonus/color.c \
         bonus/surface_normale.c bonus/world.c bonus/split_utils.c \
         bonus/cone_intersection.c bonus/specular.c bonus/shading.c

CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

CC = gcc

OBJS_M = $(M_SRCS:.c=.o)
OBJS_B = $(B_SRCS:.c=.o)

all: $(NAME)
bonus: $(NAME_B)

$(NAME): $(OBJS_M) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS_M) -o $(NAME) $(LDFLAGS)

$(NAME_B): $(OBJS_B) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_M) $(OBJS_B)

fclean: clean
	rm -f $(NAME) $(NAME_B)

re: fclean all
re_b: fclean bonus

.PHONY: all bonus clean fclean re re_b


#ifndef MINIRT_H
# define MINIRT_H

#include "../../../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include "../gnl/gnl.h"

#ifdef __APPLE__
	#define ESC_KEY 53
	#define W_KEY 13
	#define A_KEY 0
	#define S_KEY 1
	#define D_KEY 2
	#define UP 126
	#define DOWN 125
	#define LEFT 123
	#define RIGHT 124

#elif defined(__linux__)
	#define ESC_KEY 65307
	#define W_KEY 119
	#define A_KEY 97
	#define S_KEY 115
	#define D_KEY 100
	#define UP 65362
	#define DOWN 65364
	#define LEFT 65361
	#define RIGHT 65363

#else
	#error "Unsupported operating system"
#endif

# define DOTRT_ERR "Error\nThe scene file must have a .rt extension.\n"
# define FDNM_ERR "Error\nOne of the normal map file cannot be access.\n"

# define SPACE_POINT 	"must have a point in space"
# define INTENSITY		"intensity must range from 0 to 1"
# define SMOOTHNESS		"smoothness must range from 0 to 1"
# define COLOR			"rgb color components must range from 0 to 255"
# define DIAMETER_ERR	"diameter must be positive"
# define SIZE_ERR		"size must be positive"
# define REFLECTION		"reflection arguments must range from 0 to 1"
# define TEXTURE		"texture must be either checkers or a bump map"
# define DIR_VECTOR		"direction vector components must range from -1 to 1"
# define FOV_ERR		"FOV must range from 0 to 180"
# define ST_ERR			"stars option can't be implemented"
# define RADIUS			"radius and height must be positive"

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_amb
{
	double		intensity;
	int			color;
}				t_amb;

typedef struct s_cam
{
	t_vec3		origin;
	t_vec3		normal;
	double		fov;
}				t_cam;

typedef struct s_light
{
	t_vec3		origin;
	double		intensity;
	int			color;//RGB color not used in mendatory part
}				t_light;

typedef struct s_sph
{
	t_vec3		origin;
	double		diameter;
	int			color;
}				t_sph;

typedef struct s_pla
{
	t_vec3		origin;
	t_vec3		normal;
	int			color;
}				t_pla;

typedef struct s_cyl
{
	t_vec3		origin;
	t_vec3		normal;
	double		diameter;
	double		height;
	int			color;
}				t_cyl;

typedef struct s_acl
{
	t_amb		amb;
	t_cam		cam;
	t_light		light;
}				t_acl;

// Structures Parsing

// Library functions error.c
int		error(const char *msg);
int		_check_extension(char *filename);

// Library functions libft.c
void	*_memdel(void *ptr);
int     _strlen(const char *str);
char	*_strnstr(const char *big, const char *little, size_t len);
float	_atof(char *str);
int	is_space(char *s);

// Library functions split.c
char	**_split(char const *s, char c);
void	free_tab(char **tab);

// A, C, L Parsing and Filling
int		get_color(t_vec3 color); // color to int hihi
int		fill_amb(t_amb *amb, char *line);
int		fill_cam(t_cam *cam, char *line);
int		fill_light(t_light *light, char *line);


#endif


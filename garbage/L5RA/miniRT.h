#ifndef MINIRT_H
# define MINIRT_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include "gnl.h"
#include "struct.h"

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
# define SIZE_ERR		"size must be positive"
# define REFLECTION		"reflection arguments must range from 0 to 1"
# define TEXTURE		"texture must be either checkers or a bump map"
# define DIR_VECTOR		"direction vector components must range from -1 to 1"
# define FOV_ERR		"FOV must range from 0 to 180"
# define ST_ERR			"stars option can't be implemented"
# define RADIUS			"radius and height must be positive"
# define ORIGIN_ERR		"origin must have 3 coordinates"
# define ARG_ERR		"Invalid number of arguments"
# define M_PI			3.14159265358979323846
# define WIDTH			800
# define HEIGHT			600
# define ESP			0.000001

# define SP 1
# define PL 2
# define CY 3

# define EPS 0.000001

// GET SCENE
char	**add_to_map(char **scene, char *new_line);
char	**get_scene(char *filename);
int		alc_num(char **tab);
int     _check_extension(char *filename);

// SPLITS FUNCTIONS
char	**_split(char const *s, char c);

// FREE FUNCTIONS
void	free_tab(char **tab);
int     double_free(char **tab, void *ptr);

// LIBFT FUNCTIONS
int     is_digit(char c);
void    *_malloc(size_t size);
int     is_digitf(char *s);
int     is_space(char *s);
void    *_memdel(void *ptr);
int     _strlen(const char *s);
char    *_strnstr(const char *big, const char *little, size_t len);
float   _atof(char *str);

// ERROR FUNCTIONS
int     error(const char *msg);

// GETCOLORS FUNCTIONS
int     get_color(t_vec3 color);
int		valide_rgb(t_vec3 color);
t_vec3	make_vec(char **tab);
void	null_vec(t_vec3 *vec);
int		in_range(char **tab);

// FILL ACL FUNCTIONS
int     fill_amb(t_amb *amb, char *line);
int     fill_cam(t_cam *cam, char *line);
int     fill_light(t_light *light, char *line);
int		three_check(char **tab);

// FILL_OBJECTS FUNCTIONS
int     fill_sphere(t_scene *sc, char *line);
int     fill_plane(t_scene *sc, char *line);
int		fill_cylender(t_scene *sc, char *line);


// SELECT FUNCTIONS
int     select_a(t_scene *scene, char **tab);
int     select_c(t_scene *scene, char **tab);
int     select_l(t_scene *scene, char **tab);
int		selecte(t_scene *scene, char **tab);
int		is_acl(char **tab, char c);
int		not_type(char *type);
int		em_free(char *msg, char **ori, char **nor, char **tab);

// SELECT_2 FUNCTIONS
int     is_spcypl(char **tab, char type, char type2);
int     select_2(t_scene *sc, char **tab);

// VECTOR FUNCTIONS
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 v, float s);
float vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
float vec3_length(t_vec3 v);
t_vec3 vec3_normalize(t_vec3 v);

// CAMERA FUNCTIONS
t_camera    set_camera(t_scene *sc);
t_ray		ray_primary(t_camera *cam, double x, double y);

// RAYTRACING FUNCTIONS
void    ft_render(t_scene *sc);
void    image_init(t_mlx *mlx);
void	ft_draw(t_scene *sc, t_render *render, t_mlx *mlx);

// MLX FUNCTIONS
void	my_mlx_put_pixel(t_mlx *mlx, int x, int y, int color);

// RAY COLOR FUNCTIONS
t_vec3	ray_color(t_scene *sc, t_ray *ray);
int get_color(t_vec3 col);
t_vec3	add_coef(t_vec3 col1, t_vec3 col2, double ratio);

// INTERSECT FUNCTIONS
double	inter_sphere(t_ray *ray, t_objs *sp);
double	inter_plane(t_ray *ray, t_objs *pl);

// SURFACE NORMAL FUNCTIONS
t_inter	spher_normal(t_inter hold, t_objs *obj, t_ray *ray);
t_inter	plane_normal(t_inter hold, t_objs *obj, t_ray *ray);

// WORLD INTERSECT FUNCTIONS
t_inter find_inter(t_scene *sc, t_ray *ray);

// SHADE FUNCTIONS
int		shade(t_scene *sc, t_inter inter, t_light *light);
t_vec3  diffuse(t_inter inter, t_light *light, double d);

#endif
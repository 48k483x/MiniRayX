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
# define SIZE_ERR		"size must be positive"
# define REFLECTION		"reflection arguments must range from 0 to 1"
# define TEXTURE		"texture must be either checkers or a bump map"
# define DIR_VECTOR		"direction vector components must range from -1 to 1"
# define FOV_ERR		"FOV must range from 0 to 180"
# define ST_ERR			"stars option can't be implemented"
# define RADIUS			"radius and height must be positive"
# define ORIGIN_ERR		"origin must have 3 coordinates"
# define M_PI			3.14159265358979323846
# define WIDTH			1200
# define HEIGHT			800
# define ESP			0.000001
typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_amb
{
	double		intensity;
	t_vec3			color;
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
	int			color;// RGB color not used in mendatory part
}				t_light;

typedef struct s_sph
{
	t_vec3		origin;
	double		diameter;
	t_vec3			color;
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

typedef struct s_sph_l
{
	t_sph		sph;
	struct s_sph_l	*next;
}				t_sph_l;

typedef struct s_pla_l
{
	t_pla		pla;
	struct s_pla_l	*next;
}				t_pla_l;

typedef struct s_cyl_l
{
	t_cyl		cyl;
	struct s_cyl_l	*next;
}				t_cyl_l;

typedef struct s_scene
{
	t_amb		amb;
	t_cam		cam;
	t_light		light;
	t_sph_l		*sph;
	t_pla_l		*pla;
	t_cyl_l		*cyl;
}				t_scene;

typedef	struct s_camera
{
	t_vec3		origin;
	t_vec3		up;
	t_vec3		right;
	t_vec3		forward;
	double		width;
	double		height;
	double		aspratio;
	double		theeta;
}				t_camera;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_mlx;

typedef struct s_ray
{
	t_vec3		origin;
	t_vec3		dir;
}				t_ray;

typedef struct s_render
{
	t_camera	cam;
	t_ray		ray;
	t_vec3		color;
	double		px;
	double		py;
	int			x;
	int			y;
	double		scale;
}				t_render;

typedef struct sphere
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	t1;
	double	t2;
	t_vec3	oc;
}	t_sphere;

typedef struct	s_inter
{
	double		t;
	t_vec3		normal;
	t_vec3		hit;
	t_vec3			color;
}				t_inter;

// Structures Parsing

// Library functions error.c
int		error_main(const char *msg, char **tab);
int		error(const char *msg);
int		_check_extension(char *filename);
int		alc_num(char **tab);

// Library functions libft.c
void	*_malloc(size_t size);
void	*_memdel(void *ptr);
int		_strlen(const char *str);
char	*_strnstr(const char *big, const char *little, size_t len);
float	_atof(char *str);
int		is_space(char *s);
int		is_digit(char c);
int		is_digitf(char *s);

// Library functions split.c
char	**_split(char const *s, char c);
void	free_tab(char **tab);
int		double_free(char **tab, void *ptr);

// GET SCENE FUNCTIONS
char	**add_to_map(char **scene, char *new_line);
char	**get_scene(char *filename);

// A, C, L Parsing and Filling
int		get_color(t_vec3 color); // color to int hihi
int		three_check(char **tab);
int		fill_amb(t_amb *amb, char *line);
int		fill_cam(t_cam *cam, char *line);
int		fill_light(t_light *light, char *line);
int		fill_sphere(t_sph *sph, char *line);
int		fill_planet(t_pla *pla, char *line);
int		fill_cylindre(t_cyl *cyl, char *line);

// VECTOR FUNCTIONS
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 v, float s);
float vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
float vec3_length(t_vec3 v);
t_vec3 vec3_normalize(t_vec3 v);

// SP, PL, CY, A, C, L Printing
void	print_scene(t_scene *scene);

// SP, PL, CY Parsing and Filling and Select
int		selecte(t_scene *scene, char **tab);
void	free_all_l(t_scene *scene);


// RAYTRACE FUNCTIONS

// RAYTRACE COLOR FUNCTIONS
t_vec3 ray_color(t_scene *scene, t_ray *ray, char **sc);

// RAYTRACE CAMERA FUNCTIONS
int esc_key(int key, t_mlx *mlx);
t_camera set_camera(t_scene *scene);
t_ray set_ray(t_camera *cam, double x, double y);

// RAYTRACE FILE FUNCTIONS
void	ft_render(t_scene *scene, t_mlx *mlx);

// RAYTRACE INTER FUNCTIONS
t_inter	intersect(t_scene *scene, t_ray *ray, char **tab);

// RAYTRACE SUFRFACE NORMAL FUNCTIONS
t_inter sphere_normal(t_inter hold, t_scene *scene, t_ray *ray);

#endif


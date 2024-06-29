#ifndef STRUCT_H
# define STRUCT_H


typedef struct s_vec3
{
	double x;
	double y;
	double z;
}	t_vec3;

typedef struct s_amb
{
	double		ratio;
	t_vec3		color;
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
	t_vec3		color;// RGB color not used in mendatory part
}				t_light;

typedef struct s_sph
{
	t_vec3		origin;
	double		diameter;
	t_vec3		color;
}				t_sph;

typedef struct s_pla
{
	t_vec3		origin;
	t_vec3		normal;
	t_vec3		color;
}				t_pla;

typedef struct s_cyl
{
	t_vec3		origin;
	t_vec3		normal;
	double		diameter;
	double		height;
	t_vec3		color;
}				t_cyl;


typedef struct s_objs
{
	int				type;
	t_vec3			cen;
	t_vec3			dir;
	t_vec3			p;
	t_vec3			col;
	t_vec3			norm;
	struct s_objs	*next;
}	t_objs;

typedef struct s_scene
{
	t_amb		amb;
	t_cam		cam;
	t_light		light;
	t_objs		*objs;
	t_vec3		col;
}				t_scene;

typedef	struct	s_camera
{
	t_vec3	orig;
	t_vec3	up;
	t_vec3	forward;
	t_vec3	right;
	double	height;
	double	width;
	double	aspect_r;
	double	theta;
}				t_camera;

typedef struct	s_render
{
	t_camera	cam;
	int		x;
	int		y;
	double	u;
	double	v;
}			t_render;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_mlx;

typedef struct	s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}				t_ray;

#endif
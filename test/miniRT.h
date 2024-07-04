#ifndef MINIRT_H
# define MINIRT_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Key codes (keep the existing definitions)
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
#endif // __APPLE__ or __linux__


#define FOV 80
#define M_PI 3.14159265358979323846

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_amb
{
    double intensity;
    t_vec3 color;
} t_amb;

typedef struct s_cam
{
    t_vec3 origin;
    t_vec3 normal;
    double fov;
} t_cam;

typedef struct s_light
{
    t_vec3 origin;
    double intensity;
    t_vec3 color;
} t_light;

typedef struct s_sph
{
    t_vec3 origin;
    double diameter;
    t_vec3 color;
} t_sph;

typedef struct s_pla
{
    t_vec3 origin;
    t_vec3 normal;
    t_vec3 color;
} t_pla;

typedef struct s_cyl
{
    t_vec3 origin;
    t_vec3 normal;
    double diameter;
    double height;
    t_vec3 color;
} t_cyl;

typedef struct s_sph_l
{
    t_sph sph;
    struct s_sph_l *next;
} t_sph_l;

typedef struct s_pla_l
{
    t_pla pla;
    struct s_pla_l *next;
} t_pla_l;

typedef struct s_cyl_l
{
    t_cyl cyl;
    struct s_cyl_l *next;
} t_cyl_l;

typedef struct s_scene
{
    t_amb amb;
    t_cam cam;
    t_light light;
    t_sph_l *sph;
    t_pla_l *pla;
    t_cyl_l *cyl;
} t_scene;

typedef struct s_camera
{
    t_vec3 origin;
    t_vec3 up;
    t_vec3 right;
    t_vec3 forward;
    double width;
    double height;
    double aspratio;
    double theeta;
} t_camera;

typedef struct s_mlx
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int width;
    int height;
} t_mlx;

typedef struct s_ray
{
    t_vec3 origin;
    t_vec3 dir;
} t_ray;

typedef struct s_render
{
    t_camera cam;
    t_ray ray;
    t_vec3 color;
    double px;
    double py;
    int x;
    int y;
    double scale;
} t_render;

typedef struct s_inter
{
    double t;
    t_vec3 normal;
    t_vec3 hit;
    t_vec3 color;
} t_inter;

typedef struct s_light_params {
    t_vec3 point;
    t_vec3 normal;
    t_vec3 view_dir;
    t_vec3 object_color;
    t_light light;
    t_scene *scene;
} t_light_params;

typedef struct s_hook_params {
    t_mlx *mlx;
    t_scene *scene;
} Hook_params;

// Function prototypes

// vector.c
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 v, double s);
double vec3_dot(t_vec3 a, t_vec3 b);
double vec3_length(t_vec3 v);
t_vec3 vec3_multiply(t_vec3 a, t_vec3 b);
t_vec3 vec3_cross(t_vec3 a, t_vec3 b);
t_vec3 vec3_normalize(t_vec3 v);

// intersections.c
int ray_intersect_sphere(t_ray ray, t_sph sphere, t_inter *inter);
int ray_intersect_plane(t_ray ray, t_pla plane, t_inter *inter);
int ray_intersect_cylinder(t_ray ray, t_cyl cylinder, t_inter *inter);

// lighting.c
int is_in_shadow(t_ray shadow_ray, t_scene *scene, double light_distance);
t_vec3 calculate_lighting(t_light_params *params);

// scene.c
void init_scene(t_scene *scene);
void free_scene(t_scene *scene);

// render.c
void init_camera(t_camera *cam, t_cam *scene_cam);
t_vec3 ray_color(t_ray *ray, t_scene *scene);
void draw_scene(t_mlx *mlx, t_scene *scene);

// utils.c
void put_pixel(t_mlx *mlx, int x, int y, int color);
int get_color(t_vec3 color);
double deg_to_rad(double deg);
int handle_keypress(int keycode, Hook_params *params);
int handle_close(t_mlx *mlx);

#endif
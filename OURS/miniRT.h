#ifndef MINIRT_H
# define MINIRT_H

#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

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

// Vector structure
typedef struct {
    float x, y, z;
} Vec3;

// Ray structure
typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

// Sphere structure
typedef struct {
    Vec3 center;
    float radius;
    Vec3 color;
} Sphere;

// Light structure
typedef struct {
    Vec3 position;
    Vec3 color;
    float intensity;
} Light;

// Camera structure
typedef struct {
    Vec3 pos;
    Vec3 forward;
    Vec3 up;
    Vec3 right;
} Camera;

// MLX structure
typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *data;
    int bpp;
    int size_line;
    int endian;
    int width;
    int height;
} MLX;

// Function declarations
Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(Vec3 v, float s);
float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec3 vec3_normalize(Vec3 v);
int ray_intersect_sphere(Ray ray, Sphere sphere, float *t);
Vec3 calculate_lighting(Vec3 point, Vec3 normal, Vec3 view_dir, Light light, Sphere sphere);
void put_pixel(MLX *mlx, int x, int y, int color);
int get_color(Vec3 color);
void draw_scene(MLX *mlx, Sphere sphere, Light light, Camera camera);
int handle_keypress(int keycode, MLX *mlx);
int handle_close(MLX *mlx);

#define FOV 90
#define M_PI 3.14159265358979323846

#endif


#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <mlx.h>

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

#endif

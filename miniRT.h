#ifndef MINIRT_H
# define MINIRT_H

#include "minilibx-linux/mlx.h"
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

#elif defined(__linux__)
	#define ESC_KEY 65307
	#define W_KEY 119
	#define A_KEY 97
	#define S_KEY 115
	#define D_KEY 100

#else
	#error "Unsupported operating system"
#endif

typedef struct	s_vector
{
	double x;
	double y;
}				vec2;

typedef struct	s_vector3
{
	double x;
	double y;
	double z;
}				vec3;

typedef struct	s_vector4
{
	double r;
	double g;
	double b;
	double a;
}				vec4;

// utils/keys.c
int handle_key(int keycode, void *param);


// HADI RA LENDIF LKBIRA
#endif

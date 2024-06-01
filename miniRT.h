#ifndef MINIRT_H
# define MINIRT_H

#include "mlx.h"
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

// HADI RA LENDIF LKBIRA
#endif
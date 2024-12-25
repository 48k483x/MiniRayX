#include "miniRT.h"

void    my_mlx_put_pixel(t_mlx *mlx, int x, int y, int color)
{
    char    *dst;

    dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
    *(unsigned int*)dst = color;
}
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100

int handle_key(int keycode, void *param)
{
    (void)param; // To suppress unused parameter warning
    if (keycode == ESC_KEY)
    {
        printf("ESC key pressed\n");
        exit(0);
    }
    else if (keycode == W_KEY)
        printf("W key pressed\n");
    else if (keycode == A_KEY)
        printf("A key pressed\n");
    else if (keycode == S_KEY)
        printf("S key pressed\n");
    else if (keycode == D_KEY)
        printf("D key pressed\n");
    return 0;
}

int main()
{
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Key Press Example");

    mlx_key_hook(win, handle_key, NULL);
    mlx_loop(mlx);

    return 0;
}

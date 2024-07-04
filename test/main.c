#include "miniRT.h"

int main()
{
    t_mlx mlx;
    t_scene scene;

    mlx.mlx = mlx_init();
    mlx.width = 800;
    mlx.height = 600;
    mlx.win = mlx_new_window(mlx.mlx, mlx.width, mlx.height, "Ray Tracer");
    mlx.img = mlx_new_image(mlx.mlx, mlx.width, mlx.height);
    mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_len, &mlx.endian);

    init_scene(&scene);
    draw_scene(&mlx, &scene);

    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    
    Hook_params params = {&mlx, &scene};
    mlx_hook(mlx.win, 2, 1L << 0, (int (*)(int, void *))handle_keypress, &params);
    mlx_hook(mlx.win, 17, 0, handle_close, &mlx);
    mlx_loop(mlx.mlx);

    free_scene(&scene);
    return 0;
}
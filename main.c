#include "miniRT.h"

int handle_key(int keycode, void *param)
{
	(void)param;
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

void    background(void *mlx, void *win, int with, int heigh)
{
	int x;
	int y;

	x = 0;
	while (x < with)
	{
		y = 0;
		while (y < heigh)
		{
			mlx_pixel_put(mlx, win, x, y, 0xFF2D55);
			y++;
		}
		x++;
	}
}

int main()
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Key Press Example");

	mlx_key_hook(win, handle_key, NULL);
	background(mlx, win, 800, 600);
	mlx_loop(mlx);

	return 0;
}

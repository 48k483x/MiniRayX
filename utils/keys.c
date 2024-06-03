#include "../miniRT.h"

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
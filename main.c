#include "miniRT.h"

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
double	dot3(vec3 a, vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	norm3(vec3 a)
{
	return (sqrt(dot3(a, a)));
}

int vec4_color(vec4 color) {
    // Ensure color values are in the range [0, 255]
    int r = (int)(color.r * 255.0f);
    int g = (int)(color.g * 255.0f);
    int b = (int)(color.b * 255.0f);
    int a = (int)(color.a * 255.0f);
    return (a << 24 | r << 16 | g << 8 | b);
}


int main() {
    void *mlx;
    void *win;
    vec3 rayOrigin = {0.0f, 0.0f, 1.0f};
    vec3 rayDirection;
    float radius = 0.5f;
    
    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "3D Sphere");

    // Calculate aspect ratio
    float aspectRatio = 800.0f / 600.0f;

    for (int i = 0; i < 800; i++) {
        for (int j = 0; j < 600; j++) {
            // Calculate ray direction based on pixel coordinates and aspect ratio
            double ncdx = (i + 0.5) / 800 * 2 - 1;
            double ncdy = (j + 0.5) / 600 * 2 - 1;
            ncdy /= aspectRatio;

            rayDirection = (vec3){ncdx, ncdy, -1.0f}; // Adjust the z-coordinate for perspective

            // Normalize the ray direction
            double length = norm3(rayDirection);
            rayDirection.x /= length;
            rayDirection.y /= length;
            rayDirection.z /= length;

            double a = dot3(rayDirection, rayDirection);
            double b = 2.0f * dot3(rayDirection, rayOrigin);
            double c = dot3(rayOrigin, rayOrigin) - radius * radius;
            double discriminant = b * b - 4 * a * c;

            if (discriminant >= 0) {
                double t1 = (-b + sqrt(discriminant)) / (2 * a);
                double closestT = (-b - sqrt(discriminant)) / (2 * a);

                // Calculate the hit point
                vec3 hitpoint = {
                    rayOrigin.x + closestT * rayDirection.x,
                    rayOrigin.y + closestT * rayDirection.y,
                    rayOrigin.z + closestT * rayDirection.z
                };

                // Use the hit point to determine the color
                vec4 color = {(hitpoint.x + 1 / 2), (hitpoint.y + 1 / 2), (hitpoint.z + 1 / 2), 1.0f};
				printf("color : hitpoint.x = %f, hitpoint.y = %f, hitpoint.z = %f\n", hitpoint.x, hitpoint.y, hitpoint.z);
                mlx_pixel_put(mlx, win, i, j, vec4_color(color));
            } else {
                vec4 black = {0.0f, 0.0f, 0.0f, 1.0f};
                mlx_pixel_put(mlx, win, i, j, vec4_color(black));
            }
        }
    }

    mlx_key_hook(win, handle_key, NULL);
    mlx_loop(mlx);

    return 0;
}
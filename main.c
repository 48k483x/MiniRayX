#include "miniRT.h"

double	dot3(vec3 *a, vec3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

float	norm3(vec3 *a)
{
	return (sqrtf(dot3(a, a)));
}

double normalize(vec3 *a)
{
    float len;

    len = norm3(a);
    a->x /= len;
    a->y /= len;
    a->z /= len;

}

int vec4_color(vec4 color) {
    // Ensure color values are in the range [0, 255]
    int r = (int)(color.r * 255.0f);
    int g = (int)(color.g * 255.0f);
    int b = (int)(color.b * 255.0f);
    int a = (int)(color.a * 255.0f);
    return (a << 24 | r << 16 | g << 8 | b);
}

double clamp(double x, double lowerlimit, double upperlimit) {
    if (x < lowerlimit) 
        x = lowerlimit;
    if (x > upperlimit) 
        x = upperlimit;
    return x;
}

double smoothstep(double edge0, double edge1, double x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0); 
    return x * x * (3 - 2 * x);
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

            normalize(&rayDirection);

            double a = dot3(&rayDirection, &rayDirection);
            double b = 2.0f * dot3(&rayDirection, &rayOrigin);
            double c = dot3(&rayOrigin, &rayOrigin) - radius * radius;
            double discriminant = b * b - 4 * a * c;

            if (discriminant >= 0) {
                double t1 = (-b + sqrtf(discriminant)) / (2 * a);
                double closestT = (-b - sqrtf(discriminant)) / (2 * a);

                // Calculate the hit point
                vec3 hitpoint = {
                    rayOrigin.x + closestT * rayDirection.x,
                    rayOrigin.y + closestT * rayDirection.y,
                    rayOrigin.z + closestT * rayDirection.z
                };

                vec3 normal = {hitpoint.x - rayOrigin.x, hitpoint.y - rayOrigin.y, hitpoint.z - rayOrigin.z};                
                normalize(&normal);

                vec3 lightDir = {-1, -1, -1};
                normalize(&lightDir);
                vec3 minusLIGHT= {-lightDir.x, -lightDir.y, -lightDir.z};
                // normalize(&minusLIGHT);
                float d = fmax(dot3(&normal, &lightDir), 0.0f);
                d = smoothstep(0.25f, 1.0f, d);
                // d = fmin(d, 1.0f);
                printf("d = %f\n", d);
                // vec4 color = {(normal.x + 1.0) / 2.0, (normal.y + 1.0) / 2.0, (normal.z + 1.0) / 2.0, 1.0f};			
                vec4 blue = {1, 0, 1, 1.0f};
                vec4 color = {blue.r * d, blue.g * d, blue.b * d, 1.0};
                mlx_pixel_put(mlx, win, i, j, vec4_color(color));
            } 
            else {
                vec4 black = {0.0f, 0.0f, 0.0f, 1.0f};
                mlx_pixel_put(mlx, win, i, j, vec4_color(black));
            }
        }
    }

    mlx_key_hook(win, handle_key, NULL);
    mlx_loop(mlx);

    return 0;
}

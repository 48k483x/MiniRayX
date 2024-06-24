#include "srcs/include/miniRT.h"

void	initialize_window(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 600;

	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

t_ray get_ray(t_scene *scene, t_mlx *mlx, double u, double v)
{
    double aspect_ratio = (double)mlx->width / (double)mlx->height;
    double viewport_height = 2.0 * tan((scene->cam.fov / 2.0) * (M_PI / 180.0));
    double viewport_width = aspect_ratio * viewport_height;

    t_vec3 w = vec3_normalize(vec3_scale(scene->cam.normal, -1)); // Forward vector
    t_vec3 upp = {0, 1, 0}; // World up vector
    t_vec3 right = vec3_normalize(vec3_cross(upp, w)); // Right vector
    t_vec3 up = vec3_cross(w, right); // True up vector

    t_vec3 horizontal = vec3_scale(right, viewport_width);
    t_vec3 vertical = vec3_scale(up, viewport_height);

    t_vec3 lower_left_corner = vec3_sub(
        vec3_sub(
            vec3_sub(scene->cam.origin, vec3_scale(horizontal, 0.5)),
            vec3_scale(vertical, 0.5)
        ),
        w
    );

    t_vec3 u_component = vec3_scale(horizontal, u);
    t_vec3 v_component = vec3_scale(vertical, v);

    t_vec3 direction = vec3_normalize(
        vec3_add(
            vec3_add(lower_left_corner, u_component),
            v_component
        )
    );

    t_ray ray = {scene->cam.origin, direction};
    return ray;
}

int ray_intersect_sphere(t_ray *ray, t_scene *scene, float *t)
{
    double  radus;

    radus = scene->sph->sph.diameter / 2.0;
    t_vec3 oc = vec3_sub(ray->origin, scene->sph->sph.origin);
    float a = vec3_dot(ray->dir, ray->dir);
    float b = 2.0 * vec3_dot(oc, ray->dir);
    float c = vec3_dot(oc, oc) - radus * radus;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return 0;
    else
    {
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
        return 1;
    }
}

// Function to calculate color based on ray intersection (to be implemented)
int calculate_pixel_color(t_ray ray, t_scene *scene) {
    // Placeholder function for color calculation
    // In real ray tracing, this would find intersections with objects in the scene
    // and determine the color based on lighting, materials, etc.
    // For now, return a placeholder color.
    float t;
    int color = 0x000000;
    if (ray_intersect_sphere(&ray, scene, &t))
    {
        printf("scene->sph->sph.diameter: %f\n", scene->sph->sph.diameter);
        printf("sphere->sph.origin: %f %f %f\n", scene->sph->sph.origin.x, scene->sph->sph.origin.y, scene->sph->sph.origin.z);
        printf("Camera: origin(%f, %f, %f), normal(%f, %f, %f), fov: %f\n",
       scene->cam.origin.x, scene->cam.origin.y, scene->cam.origin.z,
       scene->cam.normal.x, scene->cam.normal.y, scene->cam.normal.z,
       scene->cam.fov);

        printf("intersected\n");
        color = 0x00FFFFF;
    }
    else
    {
        printf("not intersected\n");
        color = 0x000000;
    }
    return color;
}

void my_mlx_fill_window(t_mlx *mlx, t_scene *scene) {
    int x, y;
    double u, v;

    y = 0;
    while (y < mlx->height) {
        v = (double)y / (mlx->height - 1);
        x = 0;
        while (x < mlx->width) {
            u = (double)x / (mlx->width - 1);
            t_ray ray = get_ray(scene, mlx, u, v);
            int color = calculate_pixel_color(ray, scene);
            my_mlx_pixel_put(mlx, x, y, color);
            x++;
        }
        y++;
    }
}

int main(int ac, char *av[]) {
    t_scene scene = {0};
    t_mlx mlx = {0};
    char **sc;

    if (ac != 2 || !_check_extension(av[1]))
        return error("Usage:./miniRT [scene_file]");

    sc = get_scene(av[1]);
    if (sc == NULL)
        return error_main("Can't read scene file", sc);

    if (!alc_num(sc))
        return error_main("Scene must contain one A, one C and one L", sc);

    if (!selecte(&scene, sc))
        return (error_main("Error in scene file", sc));

    initialize_window(&mlx);
    my_mlx_fill_window(&mlx, &scene);

    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    mlx_loop(mlx.mlx);

    free_all_l(&scene);
    free_tab(sc);
}

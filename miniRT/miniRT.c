#include "srcs/include/miniRT.h"
#include <math.h> // Include math.h for sqrt and tan functions

void	initialize_window(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 600;

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		error("Error initializing MLX");
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "miniRT");
	if (!mlx->win)
		error("Error creating window");
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	if (!mlx->img)
		error("Error creating image");
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
	if (!mlx->addr)
		error("Error getting data address");
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void    camera_dir(t_scene *scene)
{
    scene->cam.forward = scene->cam.normal;
    scene->cam.right = vec3_cross(scene->cam.forward, (t_vec3){0, 1, 0});
    scene->cam.right = vec3_normalize(scene->cam.right);
    scene->cam.up = vec3_cross(scene->cam.right, scene->cam.forward);
    scene->cam.up = vec3_normalize(scene->cam.up);
}

int ray_intersect_sphere(t_ray *ray, t_scene *scene, float *t)
{
    double  radius;

    radius = scene->sph->sph.diameter / 2.0;
    t_vec3 oc = vec3_sub(ray->origin, scene->sph->sph.origin);
    float a = vec3_dot(ray->dir, ray->dir);
    float b = 2.0 * vec3_dot(oc, ray->dir);
    float c = vec3_dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return 0;
    else
    {
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
        return 1;
    }
}

t_ray   get_ray(t_scene *scene, float px, float py)
{
    t_ray   ray;

    ray.dir = vec3_normalize((t_vec3){
        px * scene->cam.right.x + py * scene->cam.up.x + scene->cam.forward.x,
        px * scene->cam.right.y + py * scene->cam.up.y + scene->cam.forward.y,
        px * scene->cam.right.z + py * scene->cam.up.z + scene->cam.forward.z
    });
    ray.origin = scene->cam.origin;
    return (ray);
}

void    draw_scene(t_scene *scene, t_mlx *mlx)
{
    float   aspect_ratio;
    float   scale;
    float   px, py;
    t_ray   ray;
    int     x, y;
    float   t;

    aspect_ratio = (float)mlx->width / (float)mlx->height;
    scale = tan(scene->cam.fov * 0.5 * M_PI / 180);
    
    for (x = 0; x < mlx->width; x++)
    {
        for (y = 0; y < mlx->height; y++)
        {
            px = (2 * (x + 0.5) / mlx->width - 1) * aspect_ratio * scale;
            py = (1 - 2 * (y + 0.5) / mlx->height) * scale;
            ray = get_ray(scene, px, py);
            if (ray_intersect_sphere(&ray, scene, &t))
            {
                // Uncomment and implement these lines if necessary
                // t_vec3 point = vec3_add(ray.origin, vec3_scale(ray.dir, t));
                // t_vec3 normal = vec3_normalize(vec3_sub(point, scene->sph->sph.origin));
                // t_vec3 view_dir = vec3_scale(ray.dir, -1);
                // t_vec3 color = calculate_lighting(point, normal, view_dir, scene->light, scene->sph);
                my_mlx_pixel_put(mlx, x, y, 0x00FF00); // Example color
            }
            else
                my_mlx_pixel_put(mlx, x, y, 0x000000); // Background color
        }
    }
}

int main(int ac, char *av[]) {
    t_scene scene = {0};
    t_mlx mlx = {0};
    char **sc;

    if (ac != 2 || !_check_extension(av[1]))
        return error("Usage: ./miniRT [scene_file]");
    sc = get_scene(av[1]);
    if (sc == NULL)
        return error_main("Can't read scene file", sc);
    if (!alc_num(sc))
        return error_main("Scene must contain one A, one C and one L", sc);
    if (!selecte(&scene, sc))
        return error_main("Error in scene file", sc);
    
    initialize_window(&mlx);
    draw_scene(&scene, &mlx);
    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    mlx_loop(mlx.mlx);
    free_all_l(&scene);
    free_tab(sc);
}

#include "miniRT.h"

int	error(const char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, _strlen(msg));
	write(2, "\n", 1);
	return (0);
}

void print_acl(t_amb *amb, t_light *light, t_cam *cam, t_scene *sc)
{
    printf("Ambiant light: %.2f, %.2f, %.2f\n", amb->color.x, amb->color.y, amb->color.z);
    printf("Ambiant light ratio: %.2f\n", amb->ratio);
    printf("Light Color: %.2f, %.2f, %.2f\n", light->color.x, light->color.y, light->color.z);
    printf("Light ratio: %.2f\n", light->intensity);
    printf("Light position: %.2f, %.2f, %.2f\n", light->origin.x, light->origin.y, light->origin.z);
    printf("Camera: %.2f, %.2f, %.2f\n", cam->normal.x, cam->normal.y, cam->normal.z);
    printf("Camera orientation: %.2f, %.2f, %.2f\n", cam->origin.x, cam->origin.y, cam->origin.z);
    printf("Camera fov: %.2f\n", cam->fov);

    t_objs *objs = sc->objs;
    while (objs)
    {
        printf("Object type: %d\n", objs->type);
        if (objs->type == 1)
            printf("Object type: Sphere\n");
        else if (objs->type == 2)
            printf("Object type: Plane\n");
        else if (objs->type == 3)
        printf("Object type: Cylinder\n");
        printf("Object position: %.2f, %.2f, %.2f\n", objs->cen.x, objs->cen.y, objs->cen.z);
        printf("Object direction: %.2f, %.2f, %.2f\n", objs->dir.x, objs->dir.y, objs->dir.z);
        printf("Object diameter: %.2f\n", objs->p.x);
        printf("Object height: %.2f\n", objs->p.y);
        printf("Object color: %.2f, %.2f, %.2f\n", objs->col.x, objs->col.y, objs->col.z);

        objs = objs->next;
    }
}


int main(int ac, char *av[])
{
    t_scene scene = {0};
    // t_mlx mlx = {0};
    char **sc;

    if (ac != 2 || !_check_extension(av[1]))
        return (error("Invalid arguments"));
    sc = get_scene(av[1]);
    if (!sc || !alc_num(sc))
        return (em_free("Invalid scene file", sc, NULL, NULL));
    if (!selecte(&scene, sc))
        return (em_free("Invalid scene file", sc, NULL, NULL));
    if (!select_2(&scene, sc))
        return (em_free("Invalid scene file", sc, NULL, NULL));
    print_acl(&scene.amb, &scene.light, &scene.cam, &scene);
    ft_render(&scene);
    free_tab(sc);
}
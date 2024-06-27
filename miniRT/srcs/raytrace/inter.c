#include "../include/miniRT.h"

t_inter intersect(t_scene *scene, t_ray *ray, char **tab)
{
    t_inter hold;
    t_scene *sc;
    int     i;

    sc = scene;
    hold.t = -1;
    i = -1;
    while (tab[++i])
    {
        if (tab[i][0] == 's' && sc->sph)
        {
            printf("sphere\n");
            hold = sphere_normal(hold, sc, ray);
            sc->sph = sc->sph->next;
        }
        // if (tab[i][0] == 'p' && tab[i][1] == 'l')
        // {
        //     hold = inter_plane(ray, sc->pl);
        //     sc->pl = sc->pl->next;
        // }
        // if (tab[i][0] == 't')
        // {
        //     hold = inter_cylinder(ray, sc->cyl);
        //     sc->cyl = sc->cyl->next;
        // }
    }
    return (hold);
}
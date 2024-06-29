#include "../include/miniRT.h"

t_inter intersect(t_scene *scene, t_ray *ray, char **tab)
{
    t_inter hold;
    t_scene *sc;
    int     i;

    sc = scene;
    hold.t = -1;
    i = -1;
    t_sph_l *sph = scene->sph;
    while (tab[++i])
    {
        if (tab[i][0] == 's' && sph)
        {
            hold = sphere_normal(hold, sc, ray);
            sph = sph->next;
        }
    }
    return (hold);
}
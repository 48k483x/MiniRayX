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
    t_pla_l *pla = scene->pla;
    while (tab[++i])
    {
        if (tab[i][0] == 's' && sph)
        {
            hold = sphere_normal(hold, sc, ray);
            sph = sph->next;
        }
        // if (tab[i][0] == 'p' && pla)
        // {
        //     hold = plane_normal(hold, sc, ray);
        //     pla = pla->next;
        // }
    }
    return (hold);
}
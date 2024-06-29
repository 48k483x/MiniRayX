#include "miniRT.h"

t_inter find_inter(t_scene *sc, t_ray *ray)
{
    t_inter hold;
    t_objs  *obj;

    hold.t = -1;
    obj = sc->objs;
    while (obj)
    {
        if (obj->type == 1)
            hold = spher_normal(hold, obj, ray);
        else if (obj->type == 2)
            hold = plane_normal(hold, obj, ray);
        obj = obj->next;
    }
    return (hold);
}
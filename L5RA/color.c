#include "miniRT.h"

t_vec3	add_coef(t_vec3 col1, t_vec3 col2, double ratio)
{
	t_vec3	ret;

	ret.x = col1.x * (col2.x / 255) * ratio;
	ret.y = col1.y * (col2.y / 255) * ratio;
	ret.z = col1.z * (col2.z / 255) * ratio;
	return (ret);
}

int	is_inside(t_vec3 ray, t_vec3 norm)
{
	if (vec3_dot(ray, norm) > 0)
		return (1);
	return (0);
}

t_vec3  ray_color(t_scene *sc, t_ray *ray)
{
    t_inter inter;
    t_vec3  px_col;
    t_vec3  amb;

    inter = find_inter(sc, ray);
    if (inter.t > EPS)
    {
        amb = add_coef(sc->amb.color, inter.col, sc->amb.ratio);
        if (is_inside(ray->dir, inter.norm))
            inter.norm = vec3_scale(inter.norm, -1);    
        px_col = add_coef(amb, inter.col, 1);
        return (px_col);
    }
    return (vec3_scale(sc->amb.color, sc->amb.ratio));
}
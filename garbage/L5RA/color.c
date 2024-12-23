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

t_vec3	add_color(t_vec3 col1, t_vec3 col2)
{
	t_vec3	res;

	res = vec3_add(col1, col2);
	if (res.x > 255)
		res.x = 255;
	if (res.y > 255)
		res.y = 255;
	if (res.z > 255)
		res.z = 255;
	return (res);
}

t_vec3	calcul_color(t_scene *sc, t_inter inter, t_vec3 amb)
{
	t_light		*light;
	t_vec3		ret;
	t_vec3		hit_light;
	double		d;

	ret = (t_vec3){0, 0, 0};
	light = &sc->light;
	if (!light)
		return (amb);
	if (shade(sc, inter, light))
		ret = add_color(ret, amb);
	else
	{
		hit_light = vec3_sub(light->origin, inter.hit);
		d = vec3_dot(vec3_normalize(hit_light), inter.norm);
		ret = add_color(ret, amb);
		if (d > 0)
			ret = add_color(ret, diffuse(inter, light, d));
	}
	return (ret);
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
        px_col = calcul_color(sc, inter, amb);
        printf("px_col: %f %f %f\n", px_col.x, px_col.y, px_col.z);
        return (px_col);
    }
    return (t_vec3){0, 0, 0};
}
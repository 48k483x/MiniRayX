#include "miniRT.h"

t_inter	spher_normal(t_inter hold, t_objs *obj, t_ray *ray)
{
	t_inter	inter;

	inter.t = inter_sphere(ray, obj);
	if (((hold.t > inter.t || hold.t == -1) && inter.t > EPS))
	{
		inter.col = obj->col;
		inter.hit = vec3_add(ray->orig, vec3_scale(ray->dir, inter.t));
		inter.norm = vec3_normalize(vec3_sub(inter.hit, obj->cen));
		hold = inter;
	}
	return (hold);
}

t_inter	plane_normal(t_inter hold, t_objs *obj, t_ray *ray)
{
	t_inter	inter;

	inter.t = inter_plane(ray, obj);
	if (((hold.t > inter.t || hold.t == -1) && inter.t > EPS))
	{
		inter.col = obj->col;
		inter.hit = vec3_add(ray->orig, vec3_scale(ray->dir, inter.t));
		inter.norm = obj->dir;
		if (vec3_dot(ray->dir, inter.norm) > __DBL_EPSILON__)
			inter.norm = vec3_normalize(vec3_scale(obj->dir, -1));
		hold = inter;
	}
	return (hold);
}
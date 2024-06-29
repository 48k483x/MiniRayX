#include "miniRT.h"

double	inter_sphere(t_ray *ray, t_objs *sp)
{
	t_sphere	sph;

	sph.oc = vec3_sub(ray->orig, sp->cen);
	sph.a = vec3_dot(ray->dir, ray->dir);
	sph.b = 2.0 * vec3_dot(sph.oc, ray->dir);
	sph.c = vec3_dot(sph.oc, sph.oc) - (sp->p.x / 2.0) * (sp->p.x / 2.0);
	sph.t = sph.b * sph.b - (4 * sph.a * sph.c);
	if (sph.t < EPS)
		return (-1);
	sph.t1 = (sph.b * (-1.0) - sqrt(sph.t)) / (2.0 * sph.a);
	sph.t2 = (sph.b * (-1.0) + sqrt(sph.t)) / (2.0 * sph.a);
	if (sph.t1 * sph.t2 > EPS)
	{
		if (sph.t1 > EPS)
			return (fmin(sph.t1, sph.t2));
		return (-1);
	}
	if (sph.t1 > EPS)
		return (sph.t1);
	return (sph.t2);
}

double	inter_plane(t_ray *ray, t_objs *pl)
{
	t_vec3	x;
	t_vec3	normal;
	double	t;
	double	b;
	double	a;

	normal = vec3_normalize(pl->dir);
	x = vec3_sub(ray->orig, pl->cen);
	b = vec3_dot(ray->dir, normal);
	if (b != 0)
	{
		a = vec3_dot(x, normal);
		t = -a / b;
		if (t < EPS)
			return (-1.0);
		return (t);
	}
	return (-1.0);
}
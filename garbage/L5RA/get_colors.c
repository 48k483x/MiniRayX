#include "miniRT.h"

int	in_range(char **tab)
{
	if (_atof(tab[0]) > 1.0f || _atof(tab[0]) < -1.0f||\
		_atof(tab[1]) > 1.0f || _atof(tab[1]) < -1.0f ||\
		_atof(tab[2]) > 1.0f || _atof(tab[2]) < -1.0f)
		return (0);
	return (1);
}

t_vec3	make_vec(char **tab)
{
	t_vec3	vec;

	vec.x = _atof(tab[0]);
	vec.y = _atof(tab[1]);
	vec.z = _atof(tab[2]);
	return (vec);
}

void	null_vec(t_vec3 *vec)
{
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
}

int	valide_rgb(t_vec3 color)
{
	if (color.x < 0 || color.x > 255 || color.y < 0 \
			|| color.y > 255 || color.z < 0 || color.z > 255)
		return (0);
	return (1);
}

int	get_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = fmin(255, color.x * 255);
	g = fmin(255, color.y * 255);
	b = fmin(255, color.z * 255);
	return (r << 16 | g << 8 | b);	
}
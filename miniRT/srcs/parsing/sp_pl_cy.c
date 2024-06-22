#include "../include/miniRT.h"

int fill_sphere(t_sph *sph, char *line)
{
	char    **tab;
	char    **ori;
	char    **col;
	int     color;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 2 || (tab[0][0] != 's' && tab[0][1] != 'p')\
		|| tab[0][2] != '\0')
		return error("Sphere must start with 's'");
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return error("ORIGIN_ERR");
	sph->origin = (t_vec3){_atof(ori[0]), _atof(ori[1]), _atof(ori[2])};
	if (!is_digitf(tab[2]) || _atof(tab[2]) < 0)
		return error(RADIUS);
	sph->diameter = _atof(tab[2]);
	col = _split(tab[3], ',');
	if (!three_check(col))
		return error(COLOR);
	color = get_color((t_vec3){_atof(col[0]), _atof(col[1]), _atof(col[2])});
	if (color == -1)
		return error(COLOR);
	sph->color = color;
	return (1);
}

int fill_planet(t_pla *pla, char *line)
{
	char    **tab;
	char    **ori;
	char    **nor;
	char    **col;
	int     color;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 2 || (tab[0][0] != 'p' && tab[0][1] != 'l')\
		|| tab[0][2] != '\0')
		return error("Plane must start with 'p'");
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return error("ORIGIN_ERR");
	pla->origin = (t_vec3){_atof(ori[0]), _atof(ori[1]), _atof(ori[2])};
	nor = _split(tab[2], ',');
	if (!three_check(nor))
		return error(DIR_VECTOR);
	if (_atof(nor[0]) < -1 || _atof(nor[0]) > 1 ||\
		_atof(nor[1]) < -1 || _atof(nor[1]) > 1 ||\
		_atof(nor[2]) < -1 || _atof(nor[2]) > 1)
		return error(DIR_VECTOR);
	pla->normal = (t_vec3){_atof(nor[0]), _atof(nor[1]), _atof(nor[2])};
	col = _split(tab[3], ',');
	if (!three_check(col))
		return error(COLOR);
	color = get_color((t_vec3){_atof(col[0]), _atof(col[1]), _atof(col[2])});
	if (color == -1)
		return error(COLOR);
	pla->color = color;
	return (1);
}

int fill_cylindre(t_cyl *cyl, char *line)
{
	char    **tab;
	char    **ori;
	char    **nor;
	char    **col;
	int     color;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 2 || (tab[0][0] != 'c' && tab[0][1] != 'y')\
		|| tab[0][2] != '\0')
		return error("Cylinder must start with 'cy'");
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return error("ORIGIN_ERR");
	cyl->origin = (t_vec3){_atof(ori[0]), _atof(ori[1]), _atof(ori[2])};
	nor = _split(tab[2], ',');
	if (!three_check(nor))
		return error(DIR_VECTOR);
	if (_atof(nor[0]) < -1 || _atof(nor[0]) > 1 ||\
		_atof(nor[1]) < -1 || _atof(nor[1]) > 1 ||\
		_atof(nor[2]) < -1 || _atof(nor[2]) > 1)
		return error(DIR_VECTOR);
	cyl->normal = (t_vec3){_atof(nor[0]), _atof(nor[1]), _atof(nor[2])};
	if (!is_digitf(tab[3]) || _atof(tab[3]) < 0)
		return error(RADIUS);
	cyl->diameter = _atof(tab[3]);
	if (!is_digitf(tab[4]) || _atof(tab[4]) < 0)
		return error(RADIUS);
	cyl->height = _atof(tab[4]);
	col = _split(tab[5], ',');
	if (!three_check(col))
		return error(COLOR);
	color = get_color((t_vec3){_atof(col[0]), _atof(col[1]), _atof(col[2])});
	if (color == -1)
		return error(COLOR);
	cyl->color = color;
	return (1);
}

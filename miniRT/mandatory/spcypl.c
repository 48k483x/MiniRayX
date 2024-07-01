#include "../includes/minirt.h"

t_objs  *alloc_objs(t_scene *sc)
{
	t_objs  *objs;

	objs = malloc(sizeof(t_objs));
	if (!objs)
		return (NULL);
	null_vec(&objs->cen);
	null_vec(&objs->col);
	null_vec(&objs->dir);
	null_vec(&objs->p);
	objs->next = sc->objs;
	sc->objs = objs;
	return (objs);
}

int	free_4(char **t, char **o, char **n, char **c)
{
	if (t)
		free_tab(t);
	if (o)
		free_tab(o);
	if (n)
		free_tab(n);
	if (c)
		free_tab(c);
	return (1);
}

int	in_range(char **tab)
{
	if (_atof(tab[0]) > 1.0f || _atof(tab[0]) < -1.0f||\
		_atof(tab[1]) > 1.0f || _atof(tab[1]) < -1.0f ||\
		_atof(tab[2]) > 1.0f || _atof(tab[2]) < -1.0f)
		return (0);
	return (1);
}
int	valide_rgb(t_vec color)
{
	if (color.x < 0 || color.x > 255 || color.y < 0 \
			|| color.y > 255 || color.z < 0 || color.z > 255)
		return (0);
	return (1);
}

int fill_sphere(t_scene *sc, char *line)
{
	char    **tab;
	char    **ori;
	char    **col;
	t_objs  *objs;

	tab = _split(line, ' ');
	if (tab[4])
		return em_free(ARG_ERR, tab, NULL, NULL);
	if (_strlen(tab[0]) != 2 || tab[0][0] != 's' || tab[0][1] != 'p'\
		|| tab[0][2] != '\0')
		return em_free("Sphere must start with 's'", tab, NULL, NULL);
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return em_free(ORIGIN_ERR, tab, ori, NULL);
	if (!is_digitf(tab[2]) || _atof(tab[2]) <= 0)
		return em_free(SIZE_ERR, tab, ori, NULL);
	col = _split(tab[3], ',');
	if (!three_check(col) || !valide_rgb(make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]))))
		return em_free(COLOR, tab, ori, col);
	objs = alloc_objs(sc);
	objs->type = SP;
	objs->cen = make_vec(_atof(ori[0]), _atof(ori[1]), _atof(ori[2]));
	objs->p.x = _atof(tab[2]);
	objs->col = make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]));
	return free_4(tab, ori, NULL, col);
}

int fill_plane(t_scene *sc, char *line)
{
	char    **tab;
	char    **ori;
	char    **nor;
	char    **col;
	t_objs  *objs;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 2 || tab[0][0] != 'p' || \
		tab[0][1] != 'l' || tab[0][2] != '\0' || tab[4])
		return em_free(ARG_ERR, tab, NULL, NULL);
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return em_free(ORIGIN_ERR, tab, ori, NULL);
	nor = _split(tab[2], ',');
	if (!three_check(nor) || !in_range(nor))
		return em_free(DIR_VECTOR, tab, ori, nor);
	col = _split(tab[3], ',');
	if (!three_check(col) || !valide_rgb(make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]))))
		return em_free(COLOR, tab, ori, col);
	objs = alloc_objs(sc);
	objs->type = PL;
	objs->cen = make_vec(_atof(ori[0]), _atof(ori[1]), _atof(ori[2]));
	objs->dir = make_vec(_atof(nor[0]), _atof(nor[1]), _atof(nor[2]));
	objs->col = make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]));
	return free_4(tab, ori, nor, col);
}

int fill_cylender(t_scene *sc, char *line)
{
	char    **tab;
	char    **ori;
	char    **nor;
	char	**col;
	t_objs  *objs;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 2 || tab[0][0] != 'c' || \
		tab[0][1] != 'y' || tab[0][2] != '\0' || tab[6])
		return (em_free(ARG_ERR, tab, NULL, NULL));
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return (em_free(ORIGIN_ERR, tab, ori, NULL));
	nor = _split(tab[2], ',');
	if (!three_check(nor) || !in_range(nor))
		return (em_free(DIR_VECTOR, tab, ori, nor));
	if (!is_digitf(tab[3]) || _atof(tab[3]) <= 0 ||\
		!is_digitf(tab[4]) || _atof(tab[4]) <= 0)
		return (em_free(SIZE_ERR, tab, ori, nor));
	col = _split(tab[5], ',');
	if (!three_check(col) || !valide_rgb(make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]))))
		return (free_tab(nor), em_free(COLOR, tab, ori, col));
	objs = alloc_objs(sc);
	objs->type = CY;
	objs->cen = make_vec(_atof(ori[0]), _atof(ori[1]), _atof(ori[2]));
	objs->dir = make_vec(_atof(nor[0]), _atof(nor[1]), _atof(nor[2]));
	objs->p.x = _atof(tab[3]);
	objs->p.y = _atof(tab[4]);
	objs->col = make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]));
	return (free_4(tab, ori, nor, col));
}

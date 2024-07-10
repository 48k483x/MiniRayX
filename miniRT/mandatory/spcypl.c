#include "../includes/minirt.h"

void	init_objs(t_objs *objs, char **col, char **cen, char **dir)
{
	if (col)
		objs->col = make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]));
	if (cen)
		objs->cen = make_vec(_atof(cen[0]), _atof(cen[1]), _atof(cen[2]));
	if (dir)
		objs->dir = make_vec(_atof(dir[0]), _atof(dir[1]), _atof(dir[2]));
}

int	fill_sphere(t_scene *sc, char *line)
{
	char	**tab;
	char	**ori;
	char	**col;
	t_objs	*objs;

	tab = _split(line, ' ');
	if (tab[4])
		return (em_free(ARG_ERR, tab, NULL, NULL));
	if (_strlen(tab[0]) != 2 || tab[0][0] != 's' || tab[0][1] != 'p'\
		|| tab[0][2] != '\0')
		return (em_free("Sphere must start with 's'", tab, NULL, NULL));
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return (em_free(ORIGIN_ERR, tab, ori, NULL));
	if (!is_digitf(tab[2]) || _atof(tab[2]) <= 0)
		return (em_free(SIZE_ERR, tab, ori, NULL));
	col = _split(tab[3], ',');
	if (!three_check(col) || \
		!valide_rgb(make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]))))
		return (em_free(COLOR, tab, ori, col));
	objs = alloc_objs(sc);
	objs->type = SP;
	init_objs(objs, col, ori, NULL);
	objs->p.x = _atof(tab[2]);
	return (free_4(tab, ori, NULL, col));
}

int	fill_plane(t_scene *sc, char *line)
{
	char	**tab;
	char	**ori;
	char	**nor;
	char	**col;
	t_objs	*objs;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 2 || tab[0][0] != 'p' || \
		tab[0][1] != 'l' || tab[0][2] != '\0' || tab[4])
		return (em_free(ARG_ERR, tab, NULL, NULL));
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return (em_free(ORIGIN_ERR, tab, ori, NULL));
	nor = _split(tab[2], ',');
	if (!three_check(nor) || !in_range(nor))
		return (em_free(DIR_VECTOR, tab, ori, nor));
	col = _split(tab[3], ',');
	if (!three_check(col) || \
		!valide_rgb(make_vec(_atof(col[0]), _atof(col[1]), _atof(col[2]))))
		return (em_free(COLOR, tab, ori, col));
	objs = alloc_objs(sc);
	objs->type = PL;
	init_objs(objs, col, ori, nor);
	return (free_4(tab, ori, nor, col));
}

int	fill_cylender(t_scene *sc, char *line)
{
	t_objs	*objs;
	t_help	h;

	h.tab = _split(line, ' ');
	if (_strlen(h.tab[0]) != 2 || h.tab[0][0] != 'c' || \
		h.tab[0][1] != 'y' || h.tab[0][2] != '\0' || h.tab[6])
		return (em_free(ARG_ERR, h.tab, NULL, NULL));
	h.ori = _split(h.tab[1], ',');
	if (!three_check(h.ori))
		return (em_free(ORIGIN_ERR, h.tab, h.ori, NULL));
	h.nor = _split(h.tab[2], ',');
	if (!three_check(h.nor) || !in_range(h.nor))
		return (em_free(DIR_VECTOR, h.tab, h.ori, h.nor));
	if (check_two_nums(h.tab[3], h.tab[4]) == 0)
		return (em_free(SIZE_ERR, h.tab, h.ori, h.nor));
	h.col = _split(h.tab[5], ',');
	if (!three_check(h.col) || \
	!valide_rgb(make_vec(_atof(h.col[0]), _atof(h.col[1]), _atof(h.col[2]))))
		return (free_tab(h.nor), em_free(COLOR, h.tab, h.ori, h.col));
	objs = alloc_objs(sc);
	objs->type = CY;
	objs->p.x = _atof(h.tab[3]);
	objs->p.y = _atof(h.tab[4]);
	init_objs(objs, h.col, h.ori, h.nor);
	return (free_4(h.tab, h.ori, h.nor, h.col));
}

#include "../include/miniRT.h"

int	is_acl(char **tab, char type)
{
	if (_strlen(tab[0]) == 1 && tab[0][0] == type && tab[0][1] == '\0')
		return (1);
	return (0);
}

int	is_spcypl(char **tab, char type, char type2)
{
	if (_strlen(tab[0]) == 2 &&
		(tab[0][0] == type && tab[0][1] == type2)\
		&& tab[0][2] == '\0')
		return (1);
	return (0);
}

void	free_sphl_list(t_sph_l *sph)
{
	t_sph_l *tmp;

	while (sph)
	{
		tmp = sph;
		sph = sph->next;
		free(tmp);
	}
}

void	free_pl_l(t_pla_l *pla)
{
	t_pla_l *tmp;

	while (pla)
	{
		tmp = pla;
		pla = pla->next;
		free(tmp);
	}
}

void	free_cyl_l(t_cyl_l *cyl)
{
	t_cyl_l *tmp;

	while (cyl)
	{
		tmp = cyl;
		cyl = cyl->next;
		free(tmp);
	}
}

void	free_all_l(t_scene *scene)
{
	free_sphl_list(scene->sph);
	free_pl_l(scene->pla);
	free_cyl_l(scene->cyl);
}

int	not_type(char *line)
{
	if (_strlen(line) == 1 && line[0] == 'A' && line[1] == '\0')
		return (1);
	if (_strlen(line) == 1 && line[0] == 'C' && line[1] == '\0')
		return (1);
	if (_strlen(line) == 1 && line[0] == 'L' && line[1] == '\0')
		return (1);
	if (_strlen(line) == 2 && line[0] == 's' && line[1] == 'p'\
		&& line[2] == '\0')
		return (1);
	if (_strlen(line) == 2 && line[0] == 'p' && line[1] == 'l'\
		&& line[2] == '\0')
		return (1);
	if (_strlen(line) == 2 && line[0] == 'c' && line[1] == 'y'\
		&& line[2] == '\0')
		return (1);
	return (0);
}

int	select_a(t_scene *scene, char **tab)
{
	int	i;
	char	**sc;

	i = -1;
	while (tab[++i])
	{
		sc = _split(tab[i], ' ');
		if (!not_type(sc[0]))
			return (double_free(sc, NULL));
		if (is_acl(sc, 'A'))
		{
			if (!fill_amb(&scene->amb, tab[i]))
				return (double_free(sc, NULL));
		}
		free_tab(sc);
	}
	return (1);
}
int	select_l(t_scene *scene, char **tab)
{
	int	i;
	char	**sc;

	i = -1;
	while (tab[++i])
	{
		sc = _split(tab[i], ' ');
		if (!not_type(sc[0]))
			return (double_free(sc, NULL));
		if (is_acl(sc, 'L'))
		{
			if(!fill_light(&scene->light, tab[i]))
				return (double_free(sc, NULL));
		}
		free_tab(sc);
	}
	return (1);
}

int	select_c(t_scene *scene, char **tab)
{
	int	i;
	char	**sc;

	i = -1;
	while (tab[++i])
	{
		sc = _split(tab[i], ' ');
		if (!not_type(sc[0]))
			return (double_free(sc, NULL));
		if (is_acl(sc, 'C'))
		{
			if(!fill_cam(&scene->cam, tab[i]))
				return (double_free(sc, NULL));
		}
		free_tab(sc);
	}
	return (1);
}

int	select_sp(t_scene *scene, char **tab)
{
	int 	i;
	char	**sc;
	t_sph_l *new_node;
	t_sph_l **current;

	i = -1;
	current = &scene->sph;
	while (tab[++i])
	{
		sc = _split(tab[i], ' ');
		if (!not_type(sc[0]))
			return (double_free(sc, NULL));
		if (is_spcypl(sc, 's', 'p'))
		{
			new_node = _malloc(sizeof(t_sph_l));
			if (!fill_sphere(&new_node->sph, tab[i]))
				return (double_free(sc, new_node));
			new_node->next = NULL;
			*current = new_node;
			current = &new_node->next;
		}
		free_tab(sc);
	}
	return (1);
}

int	select_pl(t_scene *scene, char **tab)
{
	int 	i;
	char	**sc;
	t_pla_l *new_node;
	t_pla_l **current;

	i = -1;
	current = &scene->pla;
	while (tab[++i])
	{
		sc = _split(tab[i], ' ');
		if (!not_type(sc[0]))
			return (double_free(sc, NULL));
		if (is_spcypl(sc, 'p', 'l'))
		{
			new_node = _malloc(sizeof(t_pla_l));
			if (!fill_planet(&new_node->pla, tab[i]))
				return (double_free(sc, new_node));
			new_node->next = NULL;
			*current = new_node;
			current = &new_node->next;
		}
		free_tab(sc);
	}
	return (1);
}

int	select_cy(t_scene *scene, char **tab)
{
	int 	i;
	char	**sc;
	t_cyl_l *new_node;
	t_cyl_l **current;

	i = -1;
	current = &scene->cyl;
	while (tab[++i])
	{
		sc = _split(tab[i], ' ');
		if (!not_type(sc[0]))
			return (double_free(sc, NULL));
		if (is_spcypl(sc, 'c', 'y'))
		{
			new_node = _malloc(sizeof(t_cyl_l));
			if (!fill_cylindre(&new_node->cyl, tab[i]))
				return (double_free(sc, new_node));
			new_node->next = NULL;
			*current = new_node;
			current = &new_node->next;
		}
		free_tab(sc);
	}
	return (1);
}

int	return_free_l(t_scene *scene, int ret)
{
	free_all_l(scene);
	return (ret);
}

int    selecte(t_scene *scene, char **tab)
{
	if (!select_a(scene, tab))
		return (return_free_l(scene, 0));
	if (!select_c(scene, tab))
		return (return_free_l(scene, 0));
	if (!select_l(scene, tab))
		return (return_free_l(scene, 0));
	if (!select_sp(scene, tab))
		return (return_free_l(scene, 0));
	if (!select_pl(scene, tab))
		return (return_free_l(scene, 0));
	if (!select_cy(scene, tab))
		return (return_free_l(scene, 0));
	return (1);
}

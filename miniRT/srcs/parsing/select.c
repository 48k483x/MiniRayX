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

int	select_a(t_scene *scene, char **tab)
{
	int	i;
	char	**sc;

	i = -1;
	while (tab[++i])
	{
		sc = _split(tab[i], ' ');
		if (is_acl(sc, 'A'))
		{
			if (!fill_amb(&scene->amb, tab[i]))
			{
				free_tab(sc);
				return (0);
			}
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
		if (is_acl(sc, 'L'))
		{
			if(!fill_light(&scene->light, tab[i]))
			{
				free_tab(sc);
				return (0);
			}
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
		if (is_acl(sc, 'C'))
		{
			if(!fill_cam(&scene->cam, tab[i]))
			{
				free_tab(sc);
				return (0);
			}
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

int    selecte(t_scene *scene, char **tab)
{
	if (!select_a(scene, tab))
		return (0);
	if (!select_c(scene, tab))
		return (0);
	if (!select_l(scene, tab))
		return (0);
	if (!select_sp(scene, tab))
		return (0);
	if (!select_pl(scene, tab))
		return (0);
	if (!select_cy(scene, tab))
		return (0);
	return (1);
}

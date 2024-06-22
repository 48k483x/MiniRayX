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

int    selecte(t_scene *scene, char **tab)
{
	int 	i;
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
		else if (is_acl(sc, 'L'))
		{
			if(!fill_light(&scene->light, tab[i]))
			{
				free_tab(sc);
				return (0);
			}
		}
		else if (is_acl(sc, 'C'))
		{
			if(!fill_cam(&scene->cam, tab[i]))
			{
				free_tab(sc);
				return (0);
			}
		}
		else if (is_spcypl(sc, 's', 'p'))
		{
			t_sph_l *new_node = _malloc(sizeof(t_sph_l));
			if (!fill_sphere(&new_node->sph, tab[i]))
			{
				free(new_node);
				free_tab(sc);
				return (0);
			}
			new_node->next = scene->sph;
			scene->sph = new_node;
		}
		// else if (is_spcypl(sc, 'p', 'l'))
		// 	fill_planet(&scene->pla, tab[i]);
		// else if (is_spcypl(sc, 'c', 'y'))
		// 	fill_cyl(&scene->cyl, tab[i]);
		free_tab(sc);
	}
	return (1);
}

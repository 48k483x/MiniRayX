#include "../includes/minirt.h"

int	is_acl(char **tab, char type)
{
	if (_strlen(tab[0]) == 1 && tab[0][0] == type && tab[0][1] == '\0')
		return (1);
	return (0);
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

int    selecte(t_scene *scene, char **tab)
{
	if (!select_a(scene, tab))
		return (0);
	if (!select_c(scene, tab))
		return (0);
	if (!select_l(scene, tab))
		return (0);
	return (1);
}

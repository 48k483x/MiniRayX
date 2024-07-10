#include "../includes/minirt.h"

int	is_spcypl(char **tab, char type, char type2)
{
	if (_strlen(tab[0]) == 2 && (tab[0][0] == type && tab[0][1] == type2) && \
		tab[0][2] == '\0')
		return (1);
	return (0);
}

int	select_2(t_scene *sc, char **tab)
{
	int		i;
	char	**s;

	i = -1;
	while (tab[++i])
	{
		s = _split(tab[i], ' ');
		if (is_spcypl(s, 's', 'p'))
		{
			if (!fill_sphere(sc, tab[i]))
				return (double_free(s, NULL));
		}
		if (is_spcypl(s, 'p', 'l'))
		{
			if (!fill_plane(sc, tab[i]))
				return (double_free(s, NULL));
		}
		if (is_spcypl(s, 'c', 'y'))
		{
			if (!fill_cylender(sc, tab[i]))
				return (double_free(s, NULL));
		}
		free_tab(s);
	}
	return (1);
}

#include "../includes/minirt.h"


char	**add_to_map(char **scene, char *new_line)
{
	int		i;
	int		size;
	char	**new_map;

	i = 0;
	size = 0;
	while (scene && scene[size])
		size++;
	new_map = _malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		new_map[i] = scene[i];
		i++;
	}
	new_map[i] = new_line;
	new_map[i + 1] = NULL;
	_memdel(scene);
	return (new_map);
}

char **get_scene(char *filename)
{
	char 	*line;
	char	**scene;
	int		fd;

	scene = NULL;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = gnl(fd);
	while (line)
	{
		if (is_space(line))
		{
			_memdel(line);
			line = gnl(fd);
			continue;
		}
		scene = add_to_map(scene, line);
		line = gnl(fd);
	}
	close(fd);
	return (scene);
}
int    alc_num(char **tab)
{
    char   **sc;
    int     i;
    int     a_count;
    int     l_count;
    int     c_count;

	a_count = 0;
	l_count = 0;
	c_count = 0;
    i = -1;
    while (tab[++i])
    {
        sc = _split(tab[i], ' ');
        if (_strlen(sc[0]) == 1 && sc[0][0] == 'A' && sc[0][1] == '\0')
            a_count++;
        else if (_strlen(sc[0]) == 1 && sc[0][0] == 'L' && sc[0][1] == '\0')
            l_count++;
        else if (_strlen(sc[0]) == 1 && sc[0][0] == 'C' && sc[0][1] == '\0')
            c_count++;
        free_tab(sc);
    }
    if (a_count <= 1 && l_count <= 1 && c_count <= 1)
        return (1);
    return (0);
}

int _check_extension(char *filename)
{
	int i;

	i = _strlen(filename);
	if (i < 4)
		return (1);
	if (filename[i - 3] == '.' && filename[i - 2] == 'r' && filename[i - 1] == 't')
		return (1);
	return (0);

}
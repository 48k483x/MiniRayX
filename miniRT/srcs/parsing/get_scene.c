#include "../include/miniRT.h"

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
#include "srcs/include/miniRT.h"

char	**add_to_map(char **scene, char *new_line)
{
	int		i;
	int		size;
	char	**new_map;

	i = 0;
	size = 0;
	while (scene && scene[size])
		size++;
	new_map = malloc(sizeof(char *) * (size + 2));
	if (!new_map)
		return (NULL);
	while (i < size)
	{
		new_map[i] = scene[i];
		i++;
	}
	new_map[i] = new_line;
	new_map[i + 1] = NULL;
	free(scene);
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
			free(line);
			line = gnl(fd);
			continue;
		}
		scene = add_to_map(scene, line);
		line = gnl(fd);
	}
	close(fd);
	return (scene);
}

int main(int ac, char *av[])
{
	t_acl 	acl;
	char	**scene;

	scene = NULL;
	if (ac != 2 || !_check_extension(av[1]))
		return error("Usage:./miniRT [scene_file]");
	scene = get_scene(av[1]);
	if (scene == NULL)
		return error("Can't read scene file");
	for (int i = 0; scene[i]; i++)
		printf("%s\n", scene[i]);
	free_tab(scene);
}

#include "miniRT.h"

int	error(const char *msg)
{
	write(2, msg, _strlen(msg));
	write(2, "\n", 1);
	return (1);
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

int	get_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	if (color.x < 0 || color.x > 255 || color.y < 0 \
			|| color.y > 255 || color.z < 0 || color.z > 255)
		return (-1);
	r = fmin(255, color.x * 255);
	g = fmin(255, color.y * 255);
	b = fmin(255, color.z * 255);
	return (r << 16 | g << 8 | b);	
}

int	fill_amb(t_amb *amb, char *line)
{
	char **tab;
	char **colors;
	int  color;
	int i = 1;

	line[_strlen(line) - 1] = '\0';
	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 1 || tab[0][0] != 'A' || tab[0][1] != '\0')
		return error("Error: Ambiant light must start with 'A '");
	colors = _split(tab[2], ',');
	color = get_color((t_vec3){_atof(colors[0]), _atof(colors[1]), _atof(colors[2])});
	if (color == -1)
		return error(COLOR);
	if (_atof(tab[1]) < 0 || _atof(tab[1]) > 1)
		return error(INTENSITY);
	amb->intensity = _atof(tab[1]);
	amb->color = color;
	return 0;
}

int main(int ac, char *av[])
{
	if (ac != 2 || !_check_extension(av[1]))
		return error("Usage:./miniRT [scene_file]");
	
	char *line;
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return error("Error: Can't open [scene_file]");
	line = gnl(fd);
	t_amb amb;
	fill_amb(&amb, line);
	printf("intensity: %f\n", amb.intensity);
	printf("color: %d\n", amb.color);
	free(line);
	printf("atof: %f\n", _atof("0.5"));	
}
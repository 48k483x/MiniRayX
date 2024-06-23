#include "../include/miniRT.h"

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

int	three_check(char **tab)
{
	if (is_digitf(tab[0]) && is_digitf(tab[1]) && is_digitf(tab[2]))
		return (1);
	return (0);
}

int	fill_amb(t_amb *amb, char *line)
{
	char **tab;
	char **colors;
	int  color;
	int i = 1;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 1 || tab[0][0] != 'A' || tab[0][1] != '\0')
		return error("Ambiant light must start with 'A'");
	colors = _split(tab[2], ',');
	if (!three_check(colors))
		return error(COLOR);
	color = get_color((t_vec3){_atof(colors[0]), _atof(colors[1]), _atof(colors[2])});
	if (color == -1)
		return error(COLOR);
	if (!is_digitf(tab[1]) || (_atof(tab[1]) < 0 || _atof(tab[1]) > 1))
		return error(INTENSITY);
	amb->intensity = _atof(tab[1]);
	amb->color = color;
	free_tab(colors);
	free_tab(tab);
	return (1);
}

int	fill_cam(t_cam *cam, char *line)
{
	char **tab;
	char **ori;
	char **nor;
	int i = 1;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 1 || tab[0][0] != 'C' || tab[0][1] != '\0')
		return error("Camera must start with 'C'");
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return error("ORIGIN_ERR");
	cam->origin = (t_vec3){_atof(ori[0]), _atof(ori[1]), _atof(ori[2])};
	nor = _split(tab[2], ',');
	if (!three_check(nor))
		return error(DIR_VECTOR);
	if (_atof(nor[0]) < -1 || _atof(nor[0]) > 1 ||\
		_atof(nor[1]) < -1 || _atof(nor[1]) > 1 ||\
		_atof(nor[2]) < -1 || _atof(nor[2]) > 1)
		return error(DIR_VECTOR);
	cam->normal = (t_vec3){_atof(nor[0]), _atof(nor[1]), _atof(nor[2])};
	if (!is_digitf(tab[3]) || (_atof(tab[3]) < 0 || _atof(tab[3]) > 180))
		return error(FOV_ERR);
	cam->fov = _atof(tab[3]);
	free_tab(ori);
	free_tab(nor);
	free_tab(tab);
	return (1);
}

int	fill_light(t_light *light, char *line)
{
	char **tab;
	char **ori;
	char **colors;
	int color;
	int i = 1;

	tab = _split(line, ' ');
	if (_strlen(tab[0]) != 1 || tab[0][0] != 'L' || tab[0][1] != '\0')
		return error("Error: Light must start with 'l'");
	ori = _split(tab[1], ',');
	if (!three_check(ori))
		return error("ORIGIN_ERR");
	light->origin = (t_vec3){_atof(ori[0]), _atof(ori[1]), _atof(ori[2])};
	if (!is_digitf(tab[2]) || _atof(tab[2]) < 0 || _atof(tab[2]) > 1)
		return error(INTENSITY);
	light->intensity = _atof(tab[2]);
	colors = _split(tab[3], ',');
	if (!three_check(colors))
		return error(COLOR);
	color = get_color((t_vec3){_atof(colors[0]), _atof(colors[1]), _atof(colors[2])});
	if (color == -1)
		return error(COLOR);
	light->color = color;
	free_tab(ori);
	free_tab(colors);
	free_tab(tab);
	return (1);
}
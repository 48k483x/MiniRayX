#include "../includes/minirt.h"

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

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	*_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	return (ptr);
}

int	is_digitf(char *s)
{
	int	i;
	int	dot;

	dot = 0;
	i = 0;
	if (s == NULL || *s == '\0')
		return (0);
	if (s[i] == '-')
		i++;
	if (s[i] == '\0' || s[i] == '.')
		return (0);
	while (s[i])
	{
		if (s[0] == '.' || s[_strlen(s) - 1] == '.')
			return (0);
		if (s[i] == '.')
			dot++;
		if ((!is_digit(s[i]) && s[i] != '.') || dot > 1)
			return (0);
		i++;
	}
	return (1);
}

void	*_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

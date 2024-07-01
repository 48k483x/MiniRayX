#include "../includes/minirt.h"

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
	int i;
	int dot;

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


int	is_space(char *s)
{
	int i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
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

int	_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		while ((i + j) < len && big[i + j] == little[j] && big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		j = 0;
		i++;
	}
	return (NULL);
}

float	_atof(char *str)
{
	float	res;
	float	sign;
	int		i;
	float	factor;

	if (!str)
		return (-1);
	i = 0;
	factor = 1.0f;
	res = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			factor /= 10.0f;
			res += (str[i] - '0') * factor;
			i++;
		}
	}
	return (res * sign);
}
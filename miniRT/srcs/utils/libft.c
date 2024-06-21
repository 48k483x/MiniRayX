#include "../include/miniRT.h"

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
			res = (str[i] - '0') * factor;
			i++;
		}
	}
	return (res * sign);
}

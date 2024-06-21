#include "../include/miniRT.h"

int	error(const char *msg)
{
	write(2, "Error: ", 7);
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
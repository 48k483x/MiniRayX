#include "../include/miniRT.h"

int		error_main(const char *msg, char **tab)
{
    write(2, "Error: ", 7);
	write(2, msg, _strlen(msg));
	write(2, "\n", 1);
    if (tab)
        free_tab(tab);
	return (0);
}

int	error(const char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, _strlen(msg));
	write(2, "\n", 1);
	return (0);
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
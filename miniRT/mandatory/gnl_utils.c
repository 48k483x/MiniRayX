#include "../includes/minirt.h"

char	*gnl(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return (next_line);
}

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (clean_node == NULL || buf == NULL)
		return ;
	last_node = find_lst_node(*list);
	i = 0;
	j = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] && last_node->content[++i])
		buf[j++] = last_node->content[i];
	buf[j] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

void	create_list(t_list **list, int fd)
{
	char	*buf;
	int		readed;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		readed = read(fd, buf, BUFFER_SIZE);
		if (!readed)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		append(list, buf);
	}
}

void	append(t_list **list, char *buf)
{
	t_list	*lst_node;
	t_list	*new_node;

	lst_node = find_lst_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
		lst_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

char	*get_line(t_list *list)
{
	char	*next_line;
	int		str_len;

	if (NULL == list)
		return (NULL);
	str_len = len_to_newline(list);
	next_line = malloc(str_len + 1);
	if (!next_line)
		return (NULL);
	copy_str(list, next_line);
	return (next_line);
}

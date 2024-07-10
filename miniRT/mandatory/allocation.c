#include "../includes/minirt.h"

// void	ft_err(char *err)
// {
// 	printf("Error : %s\n", err);
// 	ft_collect(&g_root, g_root);
// 	exit(1);
// }

// t_scene	*alloc_scence(void)
// {
// 	t_scene	*sc;

// 	g_root = NULL;
// 	sc = ft_malloc(&g_root, (sizeof(t_scene)));
// 	if (!sc)
// 		return (NULL);
// 	sc->objs = NULL;
// 	sc->amb.count = 0;
// 	sc->cam.count = 0;
// 	return (sc);
// }

t_objs	*alloc_objs(t_scene *sc)
{
	t_objs	*new_obj;

	new_obj = malloc(sizeof(t_objs));
	if (!new_obj)
		return (NULL);
	null_vec(&(new_obj->col));
	null_vec(&(new_obj->cen));
	null_vec(&(new_obj->dir));
	null_vec(&(new_obj->p));
	new_obj->next = sc->objs;
	sc->objs = new_obj;
	return (new_obj);
}

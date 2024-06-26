#include "srcs/include/miniRT.h"

int main(int ac, char *av[]) {
    t_scene scene = {0};
    t_mlx mlx = {0};
    char **sc;

    if (ac != 2 || !_check_extension(av[1]))
        return error("Usage: ./miniRT [scene_file]");
    sc = get_scene(av[1]);
    if (sc == NULL)
        return error_main("Can't read scene file", sc);
    if (!alc_num(sc))
        return error_main("Scene must contain one A, one C and one L", sc);
    if (!selecte(&scene, sc))
        return error_main("Error in scene file", sc);
    ft_render(&scene, &mlx);
    free_all_l(&scene);
    free_tab(sc);
}

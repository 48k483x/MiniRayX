#include "srcs/include/miniRT.h"

int main(int ac, char *av[])
{
	if (ac != 2 || !_check_extension(av[1]))
		return error("Usage:./miniRT [scene_file]");
	
	char *line;
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return error("Can't open [scene_file]");
	line = gnl(fd);
	t_amb amb;
	fill_amb(&amb, line);
	printf("intensity: %f\n", amb.intensity);
	printf("color: %d\n", amb.color);
	free(line);
	line = gnl(fd);
	t_cam cam;
	fill_cam(&cam, line);
	printf("origin: %f %f %f\n", cam.origin.x, cam.origin.y, cam.origin.z);
	printf("normal: %f %f %f\n", cam.normal.x, cam.normal.y, cam.normal.z);
	printf("fov: %f\n", cam.fov);
	free(line);
	line = gnl(fd);
	t_light light;
	fill_light(&light, line);
	printf("origin: %f %f %f\n", light.origin.x, light.origin.y, light.origin.z);
	printf("intensity: %f\n", light.intensity);
	printf("color: %d\n", light.color);
}

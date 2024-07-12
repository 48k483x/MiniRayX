/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:27:38 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/12 07:22:44 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"
# include "gnl.h"
# include "structs.h"

# define WIDTH 1920
# define HEIGHT 1080
# define EPS 0.000001
# define CY 1
# define PL 2
# define SP 3
# define CO 4
# define M_PI 3.14159265358979323846
# define DOTRT_ERR "Error\nThe scene file must have a .rt extension.\n"
# define FDNM_ERR "Error\nOne of the normal map file cannot be access.\n"
# define SPACE_POINT "must have a point in space"
# define INTENSITY "intensity must range from 0 to 1"
# define SMOOTHNESS "smoothness must range from 0 to 1"
# define COLOR "rgb color components must range from 0 to 255"
# define SIZE_ERR "size must be positive"
# define REFLECTION "reflection arguments must range from 0 to 1"
# define TEXTURE "texture must be either checkers or a bump map"
# define DIR_VECTOR "direction vector components must range from -1 to 1"
# define FOV_ERR "FOV must range from 0 to 180"
# define ST_ERR "stars option can't be implemented"
# define RADIUS "radius and height must be positive"
# define ORIGIN_ERR "origin must have 3 coordinates"
# define ARG_ERR "Invalid number of arguments"

// ERROR FUNCTIONS
int			error(const char *msg);

// LIBFT FUNCTIONS
int			is_digit(char c);
void		*_malloc(size_t size);
int			is_digitf(char *s);
int			is_space(char *s);
void		*_memdel(void *ptr);
int			_strlen(const char *s);
char		*_strnstr(const char *big, const char *little, size_t len);
float		_atof(char *str);
int			not_type(char *line);

// GET SCENE
char		**add_to_map(char **scene, char *new_line);
char		**get_scene(char *filename);
int			alc_num(char **tab);
int			_check_extension(char *filename);

// SPLITS FUNCTIONS
char		**_split(char const *s, char c);

// FREE FUNCTIONS
void		free_tab(char **tab);
int			double_free(char **tab, void *ptr);

// FILL ACL FUNCTIONS
int			fill_amb(t_amb *amb, char *line);
int			fill_cam(t_cam *cam, char *line);
int			fill_light(t_light *light, char *line);
int			three_check(char **tab);

// FILL_OBJECTS FUNCTIONS
int			fill_sphere(t_scene *sc, char *line);
int			fill_plane(t_scene *sc, char *line);
int			fill_cylender(t_scene *sc, char *line);

// SELECT FUNCTIONS
int			selecte(t_scene *scene, char **tab);
int			em_free(char *msg, char **ori, char **nor, char **tab);

// TOOLS FUNCTIONS
int			free_4(char **t, char **o, char **n, char **c);
int			in_range(char **tab);
int			check_two_nums(char *n1, char *n2);

// SELECT_2 FUNCTIONS
int			select_2(t_scene *sc, char **tab);

// allocation
t_objs		*alloc_objs(t_scene *sc);


// vectors
void		null_vec(t_vec *v);
t_vec		get_normalized(t_vec v);
void		normalize(t_vec *v);
double		get_norm2(t_vec v);
t_vec		sub_vec(t_vec u, t_vec v);
t_vec		add_vec(t_vec u, t_vec v);
t_vec		mult_vec(t_vec v, double a);
t_vec		vect_cross(t_vec u, t_vec v);
double		dot_product(t_vec u, t_vec v);
double		module_v(t_vec v);
t_vec		div_vect(t_vec v, double a);
t_vec		make_vec(double x, double y, double z);

/*rendring */
void		ft_render(t_scene *sc);

/* camera */
t_camera	set_camera(t_scene *sc);
t_CamRay	ray_primary(t_camera *cam, double v, double u);
t_vec		ray_at(t_CamRay *ray, double t);

/* intersections*/
t_inter		find_inter(t_CamRay *ray, t_scene *sc);
double		inter_sphere(t_CamRay *ray, t_objs *sp);
double		inter_plane(t_CamRay *ray, t_objs *pl);
double		inter_cylinder(t_CamRay *ray, t_objs *cy);

/* mlx funct */
int			red_button(t_vars *vars);
int			handle_key(int key, t_vars *vars);
void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

// color
t_vec		add_coef(t_vec col1, t_vec col2, double ratio);
int			create_rgb(int r, int g, int b);
t_vec		add_color(t_vec col1, t_vec col2);
t_vec		ray_color(t_CamRay *ray, t_scene *sc);
t_vec		colorize(double r, double g, double b);
t_vec		diffuse(t_inter inter, t_light *light, double d);
int			shade(t_scene *sc, t_inter inter, t_light *light);
int			valide_rgb(t_vec color);

// surface normal
int			is_inside(t_vec ray, t_vec norm);
t_inter		spher_normal(t_inter hold, t_objs *obj, t_CamRay *ray);
t_inter		plane_normal(t_inter hold, t_objs *obj, t_CamRay *ray);
t_inter		cylinder_normal(t_inter hold, t_objs *obj, t_CamRay *ray);

#endif

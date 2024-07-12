/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahrou <achahrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:27:41 by achahrou          #+#    #+#             */
/*   Updated: 2024/07/12 06:42:23 by achahrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* img info struct */

typedef struct s_help
{
	char	**col;
	char	**ori;
	char	**nor;
	char	**tab;
	float	res;
	float	sign;
	int		i;
	float	factor;
}				t_help;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_inter
{
	double	t;
	t_vec	col;
	t_vec	hit;
	t_vec	norm;
}	t_inter;

typedef struct t_cam
{
	t_vec	cen;
	t_vec	dir;
	double	fov;
	int		count;
}	t_cam;

typedef struct s_light
{
	t_vec			src;
	double			ratio;
	t_vec			col;
}	t_light;

typedef struct s_amb
{
	t_vec	col;
	double	ratio;
	int		count;
}	t_amb;

typedef struct s_objs
{
	int				type;
	t_vec			cen;
	t_vec			dir;
	t_vec			p;
	t_vec			col;
	t_vec			norm;
	struct s_objs	*next;
}	t_objs;

typedef struct s_scene
{
	t_vec	col;
	t_cam	cam;
	t_light	light;
	t_amb	amb;
	t_objs	*objs;
}	t_scene;

/* camera */
typedef struct Camera_Setup
{
	t_vec		orig;
	t_vec		up;
	t_vec		right;
	t_vec		forward;
	double		height;
	double		width;
	double		aspect_r;
	double		theta;
}	t_camera;

typedef struct CamRay
{
	t_vec	origin;
	t_vec	dir;
}	t_CamRay;

/* rendring */
typedef struct render
{
	t_vars		vars;
	t_img_data	img;
	double		v;
	double		u;
	int			x;
	int			y;
	t_camera	cam;
	t_CamRay	ray_;
	t_vec		ray_col;
}	t_render;

// Intersection 

typedef struct sphere
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	t1;
	double	t2;
	t_vec	oc;
}	t_sphere;

typedef struct cylinder
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	t1;
	double	t2;
	double	delta;
	double	y0;
	double	y1;
	t_vec	oc;
	t_vec	normal;
}	t_cylinder;

#endif
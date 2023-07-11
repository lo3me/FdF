/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:50:38 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/10 15:46:31 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

/**
 * @param x the abscissa of the point
 * @param y the ordinate of the point
 * @param altitude the z-like height
 * @param eol represents the last point in a line in the map file
*/
typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	int			x0;
	int			y0;
	int			z0;
	int			eol;
}				t_point;

/**
 * @brief Holds the window width and height, and the scale factors
*/
typedef struct meta_s
{
	size_t		w_width;
	size_t		w_height;
	double		translate_x;
	double		translate_y;
	double		translate_z;
	double		translate_x_iso;
	double		translate_y_iso;
	double		scale_x;
	double		scale_y;
	double		scale_z;
	double		rotate_x;
	double		rotate_y;
	double		rotate_z;
	int			bg_color;
	keys_t		key;
	action_t	mouse_action;
}				t_meta;

typedef struct s_map
{
	t_point		**points;
	size_t		width;
	size_t		height;
	size_t		depth;
}				t_map;

typedef struct s_ctx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_meta		*meta;
	t_map		*map;
}				t_ctx;

void			terminate(char *msg, int status);

t_map			*map_from_file(int fd);

void			render(t_ctx *ctx);

void			loop_and_terminate(t_ctx *ctx, int fd);
void			terminate(char *msg, int status);
void			free_ctx(t_ctx *ctx);
/**
 * Draws a line using Bresenham's algorithm
*/
void			draw_line(t_ctx *ctx, t_point p1, t_point p2);

/* Projectors */

void			p_base(t_point *p, t_ctx *ctx);
void			p_isometric(t_point *p, t_ctx *ctx);
void			p_center(t_point *p, t_ctx *ctx);

t_ctx			*apply_factors(t_ctx *ctx);
t_ctx			*map_apply(t_ctx *ctx, void (*fn)(t_point *, t_ctx *));
t_ctx			*map_rotate_y(t_ctx *ctx);

#endif

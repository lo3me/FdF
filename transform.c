/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:24:49 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/09 20:07:23 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	p_center(t_point *p, t_ctx *ctx)
{
	p->x += (ctx->meta->w_width - (ctx->map->width * ctx->meta->scale_x)) / 2;
	p->y += (ctx->meta->w_height - (ctx->map->height * ctx->meta->scale_y)) / 2;
}

void	p_base(t_point *p, t_ctx *ctx)
{
	p->x = (p->x0 + ctx->meta->translate_x) * ctx->meta->scale_x;
	p->y = (p->y0 + ctx->meta->translate_y) * ctx->meta->scale_y;
	p->z = (p->z0 - ctx->meta->translate_z) * ctx->meta->scale_z;
}

void	p_isometric(t_point *p, t_ctx *ctx)
{
	int				x;
	int				deg;
	static double	tsin;
	static double	tcos;

	(void)ctx;
	if (!tsin && !tcos)
	{
		deg = 40;
		tsin = sin(deg * M_PI / 180);
		tcos = cos(deg * M_PI / 180);
	}
	x = p->x;
	p->x = (x - p->y) * tcos + ctx->meta->translate_x_iso;
	p->y = ((x + p->y) * tsin) + ctx->meta->translate_y_iso - p->z;
}

void	p_rotate_y(t_point *p, double tsin, double tcos)
{
	int	x0;

	x0 = p->x;
	p->x = p->x * tcos + p->z * tsin;
	p->z = p->z * tcos - x0 * tsin;
}

t_ctx	*map_rotate_y(t_ctx *ctx)
{
	size_t	i;
	size_t	j;
	double	tsin;
	double	tcos;

	if (!ctx->meta->rotate_x)
		return (ctx);
	tsin = sin(ctx->meta->rotate_x);
	tcos = cos(ctx->meta->rotate_x);
	i = 0;
	while (ctx->map->points[i])
	{
		j = 0;
		while (!ctx->map->points[i][j].eol)
			p_rotate_y(&ctx->map->points[i][j++], tsin, tcos);
		i++;
	}
	return (ctx);
}

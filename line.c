/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:14:09 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/10 16:05:56 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	process_err(t_point *p1, t_point *p2, int *d, int *err)
{
	int	err2;

	err2 = 2 * (*err);
	if (err2 > -(d[1]))
	{
		*err -= d[1];
		if (p1->x < p2->x)
			p1->x++;
		else
			p1->x--;
	}
	if (err2 < d[0])
	{
		*err += d[0];
		if (p1->y < p2->y)
			p1->y++;
		else
			p1->y--;
	}
}

void	draw_line(t_ctx *ctx, t_point p1, t_point p2)
{
	int	step;
	int	bigger_z;
	int	d[2];
	int	err;
	int	color;

	step = 0;
	d[0] = abs(p2.x - p1.x);
	d[1] = abs(p2.y - p1.y);
	bigger_z = fmax(abs(p1.z0), abs(p2.z0));
	err = d[0] - d[1];
	while (p1.x != p2.x || p1.y != p2.y)
	{
		step++;
		color = 0xFFFFFF00 | (uint8_t)(fmin((bigger_z * step)
					/ (ctx->map->depth * 0.15), 0xFF));
		if (p1.x > -1 && p1.y > -1 && p1.x < (int)ctx->meta->w_width
			&& p1.y < (int)ctx->meta->w_height)
			mlx_put_pixel(ctx->img, p1.x, p1.y, color);
		process_err(&p1, &p2, d, &err);
	}
}

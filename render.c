/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:39:12 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/09 20:00:02 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	render_map(t_ctx *ctx)
{
	size_t	i;
	size_t	j;
	size_t	prev_j;

	apply_factors(ctx);
	i = 0;
	prev_j = 0;
	while (ctx->map->points[i])
	{
		j = 0;
		while (!ctx->map->points[i][j].eol)
		{
			if (i != 0 && j < prev_j)
				draw_line(ctx, ctx->map->points[i][j],
					ctx->map->points[i - 1][j]);
			if (j != 0)
				draw_line(ctx, ctx->map->points[i][j],
					ctx->map->points[i][j - 1]);
			j++;
		}
		prev_j = j;
		i++;
	}
}

void	render(t_ctx *ctx)
{
	size_t	i;
	size_t	j;

	if (ctx->img)
		mlx_delete_image(ctx->mlx, ctx->img);
	ctx->img = mlx_new_image(ctx->mlx, ctx->meta->w_width, ctx->meta->w_height);
	j = 0;
	while (j < ctx->meta->w_height)
	{
		i = 0;
		while (i < ctx->meta->w_width)
			mlx_put_pixel(ctx->img, i++, j, ctx->meta->bg_color);
		j++;
	}
	render_map(ctx);
	mlx_image_to_window(ctx->mlx, ctx->img, 0, 0);
}

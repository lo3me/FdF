/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:20:54 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/10 16:56:40 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	key_hook(mlx_key_data_t data, void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	if (data.action == MLX_PRESS || data.action == MLX_REPEAT)
		ctx->meta->key = data.key;
	else
		ctx->meta->key = 0;
	if (data.key == MLX_KEY_ESCAPE)
		mlx_close_window(ctx->mlx);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_ctx	*ctx;

	(void)xdelta;
	ctx = (t_ctx *)param;
	if (ctx->meta->scale_y + (ydelta) < 0)
		return ;
	ctx->meta->scale_y += ydelta * 1.5;
	ctx->meta->scale_x += ydelta * 1.5;
	ctx->meta->scale_z += ydelta * .1;
	render(ctx);
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_ctx	*ctx;

	(void)mods;
	ctx = (t_ctx *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT)
		ctx->meta->mouse_action = action;
}

static void	key_bind_ctrl(t_ctx *ctx, double xpos, double ypos, double last[2])
{
	if (!(last[0] && last[1]))
		return ;
	if (ctx->meta->key == MLX_KEY_R)
	{
		ctx->meta->rotate_x += ((xpos - last[0]) / 4) * M_PI / 180;
		ctx->meta->rotate_y += ((ypos - last[1]) / 4) * M_PI / 180;
		render(ctx);
	}
	if (ctx->meta->key == MLX_KEY_G)
	{
		ctx->meta->translate_x_iso += xpos - last[0];
		ctx->meta->translate_y_iso += ypos - last[1];
		render(ctx);
	}
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_ctx			*ctx;
	static double	last[2];
	static int		update;

	if (!update)
		update = 0;
	if (update != 1)
	{
		update++;
		return ;
	}
	update = 0;
	ctx = (t_ctx *)param;
	if (ctx->meta->mouse_action == MLX_PRESS)
	{
		key_bind_ctrl(ctx, xpos, ypos, last);
		last[0] = xpos;
		last[1] = ypos;
	}
	else
	{
		last[0] = 0;
		last[1] = 0;
	}
}

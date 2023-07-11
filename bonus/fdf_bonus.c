/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:11:54 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/09 20:28:44 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "fdf_bonus.h"

int	main(int argc, char **argv)
{
	t_ctx	*ctx;
	int		fd;

	if (argc != 2)
		terminate("usage: ./fdf [MAP].fdf", -2);
	fd = open(argv[1], O_RDONLY, 0444);
	if (fd == -1)
		terminate("opening the file", -1);
	ctx = malloc(sizeof(t_ctx));
	ctx->map = map_from_file(fd);
	ctx->meta = &((t_meta){1920, 1080, 0, 0, 0, 80, -50, 20, 20, 2, 0, 0, 0,
			0x000000FF, 0, 0});
	ctx->mlx = mlx_init(ctx->meta->w_width, ctx->meta->w_height, "fdf", 1);
	if (!ctx->mlx)
		terminate("init mlx", -1);
	ctx->img = NULL;
	render(ctx);
	mlx_key_hook(ctx->mlx, key_hook, ctx);
	mlx_scroll_hook(ctx->mlx, scroll_hook, ctx);
	mlx_mouse_hook(ctx->mlx, mouse_hook, ctx);
	mlx_cursor_hook(ctx->mlx, cursor_hook, ctx);
	loop_and_terminate(ctx, fd);
	return (0);
}

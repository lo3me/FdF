/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:50:08 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/10 16:59:41 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_hook(mlx_key_data_t data, void *param)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)param;
	if (data.key == MLX_KEY_ESCAPE)
		mlx_close_window(ctx->mlx);
}

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
	ctx->meta = &((t_meta){512, 512, 0, 0, 0, 125, -50, 20, 20, 2, 0, 0, 0,
			0x000000FF, 0, 0});
	ctx->mlx = mlx_init(ctx->meta->w_width, ctx->meta->w_height, "fdf", 1);
	if (!ctx->mlx)
		terminate("init mlx", -1);
	ctx->img = NULL;
	render(ctx);
	mlx_key_hook(ctx->mlx, key_hook, ctx);
	loop_and_terminate(ctx, fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:11:31 by mmomeni           #+#    #+#             */
/*   Updated: 2023/07/09 20:15:47 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	terminate(char *msg, int status)
{
	if (msg)
	{
		if (status == -1)
			perror(msg);
		else if (status != 0)
			ft_putendl_fd(msg, STDERR_FILENO);
		else
			ft_putendl_fd(msg, STDOUT_FILENO);
	}
	exit(status);
}

void	free_ctx(t_ctx *ctx)
{
	while (ctx->map->height--)
		free(ctx->map->points[ctx->map->height]);
	free(ctx->map->points);
	free(ctx->map);
	free(ctx);
}

void	loop_and_terminate(t_ctx *ctx, int fd)
{
	close(fd);
	mlx_loop(ctx->mlx);
	mlx_terminate(ctx->mlx);
	free_ctx(ctx);
}

t_ctx	*map_apply(t_ctx *ctx, void (*fn)(t_point *, t_ctx *))
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ctx->map->points[i])
	{
		j = 0;
		while (!ctx->map->points[i][j].eol)
			(*fn)(&ctx->map->points[i][j++], ctx);
		i++;
	}
	return (ctx);
}

t_ctx	*apply_factors(t_ctx *ctx)
{
	map_apply(ctx, p_base);
	map_rotate_y(ctx);
	map_apply(ctx, p_isometric);
	map_apply(ctx, p_center);
	return (ctx);
}

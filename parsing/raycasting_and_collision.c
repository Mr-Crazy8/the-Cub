/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_and_collision.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:21 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/15 02:00:08 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	step_ray_x(t_mlx_helper *mlx, int *side)
{
	mlx->dist_rayx += mlx->player->deltax;
	mlx->player->mapx += mlx->stepx;
	*side = 0;
}

void	step_ray_y(t_mlx_helper *mlx, int *side)
{
	mlx->dist_rayy += mlx->player->deltay;
	mlx->player->mapy += mlx->stepy;
	*side = 1;
}

void	advance_ray(t_mlx_helper *mlx, int *side)
{
	if (mlx->dist_rayx < mlx->dist_rayy)
		step_ray_x(mlx, side);
	else
		step_ray_y(mlx, side);
}

int	check_wall_hit(t_mlx_helper *mlx)
{
	char	tile;

	tile = mlx->utils->map[mlx->player->mapy][mlx->player->mapx];
	if (tile == '1')
		return (1);
	return (0);
}

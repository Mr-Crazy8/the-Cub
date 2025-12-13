/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_and_collision.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:21 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 18:42:33 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	step_ray_x(t_mlx_helper *mlx, int *side)
{
	mlx->dist_rayX += mlx->player->deltaX;
	mlx->player->mapX += mlx->stepX;
	*side = 0;
}

void	step_ray_y(t_mlx_helper *mlx, int *side)
{
	mlx->dist_rayY += mlx->player->deltaY;
	mlx->player->mapY += mlx->stepY;
	*side = 1;
}

void	advance_ray(t_mlx_helper *mlx, int *side)
{
	if (mlx->dist_rayX < mlx->dist_rayY)
		step_ray_x(mlx, side);
	else
		step_ray_y(mlx, side);
}

int	check_wall_hit(t_mlx_helper *mlx)
{
	char	tile;

	tile = mlx->utils->map[mlx->player->mapY][mlx->player->mapX];
	if (tile == '1')
		return (1);
	return (0);
}

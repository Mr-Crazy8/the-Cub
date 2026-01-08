/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_and_collision_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:28:21 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:55:52 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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
	int		map_height;
	int		map_width;

	map_height = 0;
	while (mlx->utils->map[map_height])
		map_height++;
	if (mlx->player->mapy < 0 || mlx->player->mapy >= map_height)
		return (1);
	map_width = 0;
	while (mlx->utils->map[mlx->player->mapy][map_width])
		map_width++;
	if (mlx->player->mapx < 0 || mlx->player->mapx >= map_width)
		return (1);
	tile = mlx->utils->map[mlx->player->mapy][mlx->player->mapx];
	if (tile == '1')
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:51:34 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 17:55:52 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_ray_direction(t_player *player, int x)
{
	player->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	player->raydir_x = player->dir_x + player->plane_x * player->camera_x;
	player->raydir_y = player->dir_y + player->plane_y * player->camera_x;
	player->mapX = (int)player->pos_x;
	player->mapY = (int)player->pos_y;
}

void	calculate_delta_dist(t_player *player)
{
	if (player->raydir_x == 0)
		player->deltaX = 999999999999999999;
	else
		player->deltaX = fabs(1.0 / player->raydir_x);
	if (player->raydir_y == 0)
		player->deltaY = 999999999999999999;
	else
		player->deltaY = fabs(1.0 / player->raydir_y);
}

void	init_step_and_dist_x(t_mlx_helper *mlx_utils, t_player *player)
{
	if (player->raydir_x < 0)
	{
		mlx_utils->stepX = -1;
		mlx_utils->dist_rayX = (player->pos_x - player->mapX) * player->deltaX;
	}
	else
	{
		mlx_utils->stepX = 1;
		mlx_utils->dist_rayX = (player->mapX + 1.0
				- player->pos_x) * player->deltaX;
	}
}

void	init_step_and_dist_y(t_mlx_helper *mlx_utils, t_player *player)
{
	if (player->raydir_y < 0)
	{
		mlx_utils->stepY = -1;
		mlx_utils->dist_rayY = (player->pos_y - player->mapY) * player->deltaY;
	}
	else
	{
		mlx_utils->stepY = 1;
		mlx_utils->dist_rayY = (player->mapY + 1.0
				- player->pos_y) * player->deltaY;
	}
}

double	calculate_wall_x(int side, double pos_x, double pos_y,
		double dist_to_wall, double raydir_x, double raydir_y)
{
	double	wx;

	if (side == 1)
		wx = pos_x + dist_to_wall * raydir_x;
	else
		wx = pos_y + dist_to_wall * raydir_y;
	wx -= floor(wx);
	return (wx);
}

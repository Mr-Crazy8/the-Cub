/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:51:34 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/15 01:58:22 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_ray_direction(t_player *player, int x)
{
	player->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	player->raydir_x = player->dir_x + player->plane_x * player->camera_x;
	player->raydir_y = player->dir_y + player->plane_y * player->camera_x;
	player->mapx = (int)player->pos_x;
	player->mapy = (int)player->pos_y;
}

void	calculate_delta_dist(t_player *player)
{
	if (player->raydir_x == 0)
		player->deltax = 999999999999999999;
	else
		player->deltax = fabs(1.0 / player->raydir_x);
	if (player->raydir_y == 0)
		player->deltay = 999999999999999999;
	else
		player->deltay = fabs(1.0 / player->raydir_y);
}

void	init_step_and_dist_x(t_mlx_helper *mlx_utils, t_player *player)
{
	if (player->raydir_x < 0)
	{
		mlx_utils->stepx = -1;
		mlx_utils->dist_rayx = (player->pos_x - player->mapx) * player->deltax;
	}
	else
	{
		mlx_utils->stepx = 1;
		mlx_utils->dist_rayx = (player->mapx + 1.0
				- player->pos_x) * player->deltax;
	}
}

void	init_step_and_dist_y(t_mlx_helper *mlx_utils, t_player *player)
{
	if (player->raydir_y < 0)
	{
		mlx_utils->stepy = -1;
		mlx_utils->dist_rayy = (player->pos_y - player->mapy) * player->deltay;
	}
	else
	{
		mlx_utils->stepy = 1;
		mlx_utils->dist_rayy = (player->mapy + 1.0
				- player->pos_y) * player->deltay;
	}
}

double	calculate_wall_x(t_wall_x_params *params)
{
	double	wx;

	if (params->side == 1)
		wx = params->pos_x + params->dist_to_wall * params->raydir_x;
	else
		wx = params->pos_y + params->dist_to_wall * params->raydir_y;
	wx -= floor(wx);
	return (wx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:06:25 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:52:27 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

bool	check_blocking_by_door(t_mlx_helper *mlx, int x, int y, float threshold)
{
	int	i;

	i = 0;
	if (mlx && mlx->utils->map[y][x] == 'D')
	{
		while (i < mlx->utils->total_doors)
		{
			if (mlx->utils->doors[i].map_x == x
				&& mlx->utils->doors[i].map_y == y)
			{
				if (mlx->utils->doors[i].animation_progress < threshold)
					return (true);
				else
					return (false);
			}
			i++;
		}
		return (true);
	}
	else
		return (false);
}

bool	is_door_blocking(t_mlx_helper *mlx, int x, int y, int type)
{
	float	threshold_for_ray;
	float	threshold_for_movement;

	threshold_for_ray = 0.95;
	threshold_for_movement = 0.4;
	if (mlx && type == 0)
		return (check_blocking_by_door(mlx, x, y, threshold_for_movement));
	else if (mlx && type == 1)
		return (check_blocking_by_door(mlx, x, y, threshold_for_ray));
	return (false);
}

void	calculate_door_position(t_mlx_helper *mlx, int i,
			float *door_x, float *door_y)
{
	*door_x = mlx->utils->doors[i].map_x + 0.5;
	*door_y = mlx->utils->doors[i].map_y + 0.5;
}

float	calculate_distance_to_door(t_mlx_helper *mlx,
			float door_x, float door_y)
{
	float	diff_x;
	float	diff_y;

	diff_x = mlx->player->pos_x - door_x;
	diff_y = mlx->player->pos_y - door_y;
	return (sqrt(diff_x * diff_x + diff_y * diff_y));
}

void	reset_door_if_far(t_mlx_helper *mlx, int i, float distance)
{
	if (distance > mlx->utils->doors[i].activation_distance
		&& mlx->utils->doors[i].state == 2)
	{
		mlx->utils->doors[i].state = 0;
		mlx->utils->doors[i].animation_progress = 0.0;
	}
}

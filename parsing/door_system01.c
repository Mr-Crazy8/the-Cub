/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:03:34 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 15:23:02 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


void	start_opening_door(t_mlx_helper *mlx, int i, float distance)
{
	if (distance < mlx->utils->doors[i].activation_distance
		&& mlx->utils->doors[i].state == 0)
	{
		mlx->utils->doors[i].state = 1;
		mlx->utils->doors[i].animation_progress = 0.0;
	}
}

void	animate_door_opening(t_mlx_helper *mlx, int i)
{
	if (mlx->utils->doors[i].state == 1)
	{
		mlx->utils->doors[i].animation_progress += 0.5;
		if (mlx->utils->doors[i].animation_progress >= 1.0)
		{
			mlx->utils->doors[i].animation_progress = 1.0;
			mlx->utils->doors[i].state = 2;
		}
	}
}

void	update_single_door(t_mlx_helper *mlx, int i)
{
	float	door_x;
	float	door_y;
	float	distance;

	calculate_door_position(mlx, i, &door_x, &door_y);
	distance = calculate_distance_to_door(mlx, door_x, door_y);
	reset_door_if_far(mlx, i, distance);
	if (mlx->utils->doors[i].state == 2)
		return ;
	start_opening_door(mlx, i, distance);
	animate_door_opening(mlx, i);
}

void	update_doors_info(t_mlx_helper *mlx)
{
	int	i;

	i = 0;

	while (i < mlx->utils->total_doors)
	{
		update_single_door(mlx, i);
		i++;
	}
}

// int	check_door_hit(t_mlx_helper *mlx, int *did_we_hit_a_door)
// {
// 	char	tile;

// 	if (!mlx || !mlx->utils || !mlx->utils->map)
// 		exit(1);
// 	tile = mlx->utils->map[mlx->player->mapy][mlx->player->mapx];
// 	if (tile == 'D')
// 	{
// 		if (is_door_blocking(mlx, mlx->player->mapx, mlx->player->mapy, 1))
// 		{
// 			*did_we_hit_a_door = 1;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }


int	check_door_hit(t_mlx_helper *mlx, int *did_we_hit_a_door)
{
	char	tile;
	int		map_height;
	int		map_width;

	if (!mlx || !mlx->utils || !mlx->utils->map || !mlx->player)
		exit(1);
	
	// Get map dimensions
	map_height = 0;
	while (mlx->utils->map[map_height])
		map_height++;
	
	// Check if ray is out of bounds
	if (mlx->player->mapy < 0 || mlx->player->mapy >= map_height)
		return (0);  // No door out of bounds
	
	map_width = 0;
	while (mlx->utils->map[mlx->player->mapy][map_width])
		map_width++;
	
	if (mlx->player->mapx < 0 || mlx->player->mapx >= map_width)
		return (0);  // No door out of bounds
	
	tile = mlx->utils->map[mlx->player->mapy][mlx->player->mapx];
	if (tile == 'D')
	{
		if (is_door_blocking(mlx, mlx->player->mapx, mlx->player->mapy, 1))
		{
			*did_we_hit_a_door = 1;
			return (1);
		}
	}
	return (0);
}

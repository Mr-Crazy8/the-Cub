/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_and_collision01.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:49:42 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 23:11:26 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_collision(t_mlx_helper *mlx, int *did_we_hit_a_door)
{
	if (check_wall_hit(mlx))
		return (1);
	if (check_door_hit(mlx, did_we_hit_a_door))
		return (1);
	return (0);
}

int	check_hit(t_mlx_helper *mlx, int *did_we_hit_a_door)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		advance_ray(mlx, &side);
		hit = check_collision(mlx, did_we_hit_a_door);
	}
	return (side);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_and_movement01_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:40:56 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:56:04 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	move_right(t_player *player, char **map, t_mlx_helper *mlx)
{
	double	new_x;
	double	new_y;

	if (!mlx || !player || !map)
		return ;
	player->move_speed = 0.05;
	new_x = player->pos_x + player->dir_y * player->move_speed;
	new_y = player->pos_y - player->dir_x * player->move_speed;
	if (!check_collision_at(map, new_x, new_y, mlx))
	{
		player->pos_x = new_x;
		player->pos_y = new_y;
	}
}

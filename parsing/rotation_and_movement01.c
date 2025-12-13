/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_and_movement01.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:40:56 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 16:44:01 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	move_right(t_player *player, char **map, t_mlx_helper *mlx)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_y * player->move_speed;
	new_y = player->pos_y - player->dir_x * player->move_speed;
	if (map[(int)player->pos_y][(int)new_x] != '1'
		&& !is_door_blocking(mlx, (int)new_x, (int)player->pos_y, 0))
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1'
				&& !is_door_blocking(mlx, (int)player->pos_x, (int)new_y, 0))
		player->pos_y = new_y;
}

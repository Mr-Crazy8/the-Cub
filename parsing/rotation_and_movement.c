/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_and_movement.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:56:37 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/01 16:26:58 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	rotate_right(t_player *player, double rot)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dir_x;
	old_planex = player->plane_x;
	player->dir_x = player->dir_x * cos(-rot) - player->dir_y * sin(-rot);
	player->dir_y = old_dirx * sin(-rot) + player->dir_y * cos(-rot);
	player->plane_x = player->plane_x * cos(-rot) - player->plane_y * sin(-rot);
	player->plane_y = old_planex * sin(-rot) + player->plane_y * cos(-rot);
}

void	rotate_left(t_player *player, double rot)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dir_x;
	old_planex = player->plane_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dirx * sin(rot) + player->dir_y * cos(rot);
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_planex * sin(rot) + player->plane_y * cos(rot);
}

void	move_forward(t_player *player, char **map, t_mlx_helper *mlx)
{
	double	new_x;
	double	new_y;

	player->move_speed = 0.05;
	new_x = player->pos_x + player->dir_x * player->move_speed;
	new_y = player->pos_y + player->dir_y * player->move_speed;
	if (map[(int)player->pos_y][(int)new_x] != '1'
		&& !is_door_blocking(mlx, (int)new_x, (int)player->pos_y, 0))
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1'
		&& !is_door_blocking(mlx, (int)player->pos_x, (int)new_y, 0))
		player->pos_y = new_y;
}

void	move_back(t_player *player, char **map, t_mlx_helper *mlx)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * player->move_speed;
	new_y = player->pos_y - player->dir_y * player->move_speed;
	if (map[(int)player->pos_y][(int)new_x] != '1'
		&& !is_door_blocking(mlx, (int)new_x, (int)player->pos_y, 0))
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1'
		&& !is_door_blocking(mlx, (int)player->pos_x, (int)new_y, 0))
		player->pos_y = new_y;
}

void	move_left(t_player *player, char **map, t_mlx_helper *mlx)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_y * player->move_speed;
	new_y = player->pos_y + player->dir_x * player->move_speed;
	if (map[(int)player->pos_y][(int)new_x] != '1'
		&& !is_door_blocking(mlx, (int)new_x, (int)player->pos_y, 0))
		player->pos_x = new_x;
	if (map[(int)new_y][(int)player->pos_x] != '1'
		&& !is_door_blocking(mlx, (int)player->pos_x, (int)new_y, 0))
		player->pos_y = new_y;
}

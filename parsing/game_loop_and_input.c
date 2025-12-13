/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_and_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:14:18 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 18:19:29 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "raycasting.h"

void	game_loop(void *param)
{
	t_mlx_helper	*mlx;

	mlx = (t_mlx_helper *)param;
	clear_img(mlx);
	raycast(mlx, mlx->utils, mlx->player);
}

void	handel_key(mlx_key_data_t keydata, void *param)
{
	t_mlx_helper	*mlx;

	mlx = (t_mlx_helper *)param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			move_forward(mlx->player, mlx->utils->map, mlx);
		if (keydata.key == MLX_KEY_S)
			move_back(mlx->player, mlx->utils->map, mlx);
		if (keydata.key == MLX_KEY_A)
			move_right(mlx->player, mlx->utils->map, mlx);
		if (keydata.key == MLX_KEY_D)
			move_left(mlx->player, mlx->utils->map, mlx);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_right(mlx->player, 0.1);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_left(mlx->player, -0.1);
		if (keydata.key == MLX_KEY_ESCAPE)
			exit(0);
		update_doors_info(mlx);
		raycast(mlx, mlx->utils, mlx->player);
		mini_map(mlx);
	}
}

void	mouse_rotate_hook(double xpos, double ypos, void *param)
{
	t_mlx_helper	*mlx;
	static double	last_x;
	double			diff;
	double			sensitivity;
	double			rot;

	(void)ypos;
	last_x = -1;
	mlx = (t_mlx_helper *)param;
	if (last_x == -1)
	{
		last_x = xpos;
		return ;
	}
	diff = xpos - last_x;
	last_x = xpos;
	sensitivity = 0.002;
	rot = diff * sensitivity;
	if (rot > 0)
		rotate_left(mlx->player, rot);
	else if (rot < 0)
		rotate_right(mlx->player, -rot);
	raycast(mlx, mlx->utils, mlx->player);
}

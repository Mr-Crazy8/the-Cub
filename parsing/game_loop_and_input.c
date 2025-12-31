/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_and_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:14:18 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/31 22:14:46 by anel-men         ###   ########.fr       */
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
	mini_map(mlx);
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
	}
}

void	mouse_rotate_hook(double xpos, double ypos, void *param)
{
	t_mlx_helper	*mlx;
	double			diff;
	double			rot;

	(void)ypos;
	mlx = (t_mlx_helper *)param;
	
	// Calculate movement from window CENTER
	diff = xpos - (SCREEN_WIDTH / 2.0);
	
	// Ignore tiny movements (reduces jitter)
	if (fabs(diff) < 2.0)
		return;
	
	// Apply rotation with good sensitivity
	rot = diff * 0.002;  // Adjust 0.002 to taste (0.0015 slower, 0.003 faster)
	
	if (rot > 0)
		rotate_left(mlx->player, rot);
	else if (rot < 0)
		rotate_right(mlx->player, (rot*-1));
	
	// ⚠️ CRITICAL: Recenter cursor so it never hits screen edge
	mlx_set_mouse_pos(mlx->mlx_ptr, SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
	
	// ❌ REMOVE THIS LINE (you already render in game_loop!)
	// raycast(mlx, mlx->utils, mlx->player);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_and_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:14:18 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 21:57:59 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "raycasting.h"
void clean_mlx_helper(t_mlx_helper *mlx_utils);
void	game_loop(void *param)
{
	t_mlx_helper	*mlx;

	mlx = (t_mlx_helper *)param;
	if (!mlx)
		return ;
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_W) )
		move_forward(mlx->player, mlx->utils->map, mlx);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_S))
		move_back(mlx->player, mlx->utils->map, mlx);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_A))
		move_right(mlx->player, mlx->utils->map, mlx);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_D))
	{
		move_left(mlx->player, mlx->utils->map, mlx);
	}
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_LEFT))
		rotate_right(mlx->player, 0.1);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_RIGHT))
		rotate_left(mlx->player, 0.1);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_ESCAPE))
	{
		clean_up_utils(mlx->utils);
		clean_mlx_helper(mlx);
		exit(0);
	}
	
	update_doors_info(mlx);
	clear_img(mlx);
	raycast(mlx, mlx->utils, mlx->player);
	mini_map(mlx);
}

void	mouse_rotate_hook(double xpos, double ypos, void *param)
{
	t_mlx_helper	*mlx;
	double			diff;
	double			rot;

	(void)ypos;
	mlx = (t_mlx_helper *)param;
	if (!mlx)
		return;
	diff = xpos - (SCREEN_WIDTH / 2.0);
	if (fabs(diff) < 2.0)
		return;
	rot = diff * 0.002;
	if (rot > 0)
		rotate_left(mlx->player, rot);
	else if (rot < 0)
		rotate_right(mlx->player, (rot*-1));
	
	mlx_set_mouse_pos(mlx->mlx_ptr, SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);

}

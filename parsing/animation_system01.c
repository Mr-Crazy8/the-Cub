/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_system01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:22:29 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/04 16:18:11 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	draw_current_frame(t_mlx_helper *mlx, int x, int y)
{
	if (!mlx)
	{
		printf("draw_current_frame\n");
		exit(1);
	}
	mlx_image_to_window(mlx->mlx_ptr,
		mlx->sprit->images[mlx->sprit->current_frame],
		x,
		y);
}

void	animation_loop(void *param)
{
	t_mlx_helper	*mlx;
	static int		last_drawn = -1;
	int				x;
	int				y;

	mlx = (t_mlx_helper *)param;
	if (!mlx)
	{
		printf("animation_loop\n");
		exit(1);
	}
	if (!validate_animation_params(mlx))
		return ;
	update_animation(mlx->sprit);
	delete_previous_frame(mlx, last_drawn);
	ensure_current_frame_exists(mlx);
	calculate_sprite_position(mlx, &x, &y);
	draw_current_frame(mlx, x, y);
	last_drawn = mlx->sprit->current_frame;
}

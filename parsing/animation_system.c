/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:35:20 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 20:48:48 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	update_animation(t_sprite *anim)
{
	double	now;

	if (!anim)
		return ;
	now = mlx_get_time();
	if (now - anim->last_frame_time >= 0.2)
	{
		anim->current_frame++;
		if (anim->current_frame >= FIRE_FRAMES)
			anim->current_frame = 0;
		anim->last_frame_time = now;
	}
}

int	validate_animation_params(t_mlx_helper *mlx)
{
	if (!mlx || !mlx->sprit)
		return (0);
	return (1);
}

void	delete_previous_frame(t_mlx_helper *mlx, int last_drawn)
{
	if (!mlx)
		return;
	if (last_drawn != -1 && last_drawn != mlx->sprit->current_frame)
	{
		if (mlx->sprit->images[last_drawn])
		{
			mlx_delete_image(mlx->mlx_ptr, mlx->sprit->images[last_drawn]);
			mlx->sprit->images[last_drawn] = NULL;
		}
	}
}

void	ensure_current_frame_exists(t_mlx_helper *mlx)
{
	int	current;
	///mlx = NULL; segmentation fault
	if (!mlx)
		return;
	current = mlx->sprit->current_frame;
	if (!mlx->sprit->images[current])
	{
		mlx->sprit->images[current] = mlx_texture_to_image(
				mlx->mlx_ptr,
				&mlx->sprit->frames[current]->texture);
	}
}

void	calculate_sprite_position(t_mlx_helper *mlx, int *x, int *y)
{
	int	sprite_w;
	int	sprite_h;
	int	current;

	if (!mlx)
		return;
	current = mlx->sprit->current_frame;
	sprite_w = mlx->sprit->frames[current]->texture.width;
	sprite_h = mlx->sprit->frames[current]->texture.height;
	*x = (SCREEN_WIDTH - sprite_w) / 2;
	*y = SCREEN_HEIGHT - sprite_h + 20;
}

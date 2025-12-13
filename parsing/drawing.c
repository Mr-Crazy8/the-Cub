/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:47:31 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/10 19:23:34 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	draw_wall_slice(t_mlx_helper *mlx_utils, t_player *player, int x,
			int side, int lineHeight, int drawStart, int drawEnd,
			int real_drawStart, int real_drawEnd, int did_we_hit_a_door)
{
	int	y;

	y = drawStart;
	while (y < drawEnd)
	{
		mlx_put_pixel(mlx_utils->img, x, y,
			get_color(mlx_utils->texture, side,
				player->raydir_y, player->raydir_x,
				x, y, mlx_utils->dist_to_wall, player->pos_x, player->pos_y,
				lineHeight, real_drawStart, real_drawEnd, did_we_hit_a_door));
		y++;
	}
}

void	draw_floor(t_mlx_helper *mlx_utils, int x, int drawEnd)
{
	int	y;

	y = drawEnd;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(mlx_utils->img, x, y, 0xFF000080);
		y++;
	}
}

void	draw_ceiling(t_mlx_helper *mlx_utils, int x, int drawStart)
{
	int	y;

	y = 0;
	while (y < drawStart)
	{
		mlx_put_pixel(mlx_utils->img, x, y, 0xFFF0000);
		y++;
	}
}

void	draw_vertical_line(t_mlx_helper *mlx_utils, t_player *player,
			int x, int side, int did_we_hit_a_door)
{
	int	lineheight;
	int	drawstart;
	int	drawend;
	int	real_drawstart;
	int	real_drawend;

	lineheight = (int)(SCREEN_HEIGHT / mlx_utils->dist_to_wall);
	real_drawstart = -lineheight / 2 + SCREEN_HEIGHT / 2;
	real_drawend = lineheight / 2 + SCREEN_HEIGHT / 2;
	drawstart = real_drawstart;
	drawend = real_drawend;
	calculate_draw_bounds(&drawstart, &drawend, lineheight);
	draw_wall_slice(mlx_utils, player, x, side, lineheight, drawstart, drawend,
		real_drawstart, real_drawend, did_we_hit_a_door);
	draw_floor(mlx_utils, x, drawend);
	draw_ceiling(mlx_utils, x, drawstart);
}

void	draw_pixel_if_in_bounds(t_mlx_helper *mlx_utils, int screen_x,
			int screen_y, int color)
{
	if (screen_x < SCREEN_WIDTH && screen_y < SCREEN_HEIGHT)
		mlx_put_pixel(mlx_utils->mini_map_img, screen_x, screen_y, color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:15:02 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 22:40:50 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	draw_wall_slice(t_mlx_helper *mlx_utils, t_player *player,
			t_wall_params *params)
{
	int				y;
	t_color_params	color_params;

	if (!mlx_utils || !player || !params)
		return ;
	color_params.texture = mlx_utils->texture;
	color_params.side = params->side;
	color_params.raydir_y = player->raydir_y;
	color_params.raydir_x = player->raydir_x;
	color_params.x = params->x;
	color_params.dist_to_wall = mlx_utils->dist_to_wall;
	color_params.pos_x = player->pos_x;
	color_params.pos_y = player->pos_y;
	color_params.line_height = params->line_height;
	color_params.draw_start = params->real_draw_start;
	color_params.draw_end = params->real_draw_end;
	color_params.did_we_hit_a_door = params->did_we_hit_a_door;
	y = params->draw_start;
	while (y < params->draw_end)
	{
		color_params.y = y;
		mlx_put_pixel(mlx_utils->img, params->x, y, get_color(&color_params));
		y++;
	}
}

void	draw_floor(t_mlx_helper *mlx_utils, int x, int drawEnd)
{
	int	y;

	y = drawEnd;
	if (!mlx_utils)
		return ;
	if (x < 0 || x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		y = 0;
	if (y >= SCREEN_HEIGHT)
		return ;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(mlx_utils->img, x, y,
			convert_rgba_to_int(mlx_utils->utils->c_color[0],
				mlx_utils->utils->c_color[1],
				mlx_utils->utils->c_color[2], 255));
		y++;
	}
}

void	draw_ceiling(t_mlx_helper *mlx_utils, int x, int drawStart)
{
	int	y;

	y = 0;
	if (!mlx_utils)
		return ;
	if (x < 0 || x >= SCREEN_WIDTH)
		return ;
	if (drawStart < 0)
		return ;
	if (drawStart >= SCREEN_HEIGHT)
		drawStart = SCREEN_HEIGHT;
	while (y < drawStart)
	{
		mlx_put_pixel(mlx_utils->img, x, y,
			convert_rgba_to_int(mlx_utils->utils->f_color[0],
				mlx_utils->utils->f_color[1],
				mlx_utils->utils->f_color[2], 255));
		y++;
	}
}

void	draw_vertical_line(t_mlx_helper *mlx_utils, t_player *player,
			t_line_params *params)
{
	t_wall_params	wall_params;

	if (!mlx_utils || !player || !params)
		return ;
	wall_params.line_height = (int)(SCREEN_HEIGHT / mlx_utils->dist_to_wall);
	wall_params.real_draw_start = -wall_params.line_height
		/ 2 + SCREEN_HEIGHT / 2;
	wall_params.real_draw_end = (wall_params.line_height
			/ 2 + SCREEN_HEIGHT / 2);
	wall_params.draw_start = wall_params.real_draw_start;
	wall_params.draw_end = wall_params.real_draw_end;
	calculate_draw_bounds(&wall_params.draw_start, &wall_params.draw_end,
		wall_params.line_height);
	wall_params.x = params->x;
	wall_params.side = params->side;
	wall_params.did_we_hit_a_door = params->did_we_hit_a_door;
	draw_wall_slice(mlx_utils, player, &wall_params);
	draw_floor(mlx_utils, params->x, wall_params.draw_end);
	draw_ceiling(mlx_utils, params->x, wall_params.draw_start);
}

void	draw_pixel_if_in_bounds(t_mlx_helper *mlx_utils, int screen_x,
			int screen_y, int color)
{
	if (!mlx_utils)
		return ;
	if (screen_x < SCREEN_WIDTH && screen_y < SCREEN_HEIGHT)
		mlx_put_pixel(mlx_utils->mini_map_img, screen_x, screen_y, color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:15:02 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/14 16:59:12 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	draw_wall_slice(t_mlx_helper *mlx_utils, t_player *player,
			t_wall_params *params)
{
	int				y;
	t_color_params	color_params;

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
			t_line_params *params)
{
	t_wall_params	wall_params;

	wall_params.line_height = (int)(SCREEN_HEIGHT / mlx_utils->dist_to_wall);
	wall_params.real_draw_start = -wall_params.line_height
		/ 2 + SCREEN_HEIGHT / 2;
	wall_params.real_draw_end = wall_params.line_height / 2 + SCREEN_HEIGHT / 2;
	wall_params.draw_start = wall_params.real_draw_start;
	wall_params.draw_end = wall_params.real_draw_end;
	calculate_draw_bounds(&wall_params.draw_start, &wall_params.draw_end,
		wall_params.line_height);
	wall_params.x = params->x;
	wall_params.side = params->side;
	wall_params.did_we_hit_a_door = params->did_we_hit_a_door;
	draw_wall_slice(mlx_utils, player, &wall_params);
	draw_floor(mlx_utils, params->x, wall_params. draw_end);
	draw_ceiling(mlx_utils, params->x, wall_params.draw_start);
}

void	draw_pixel_if_in_bounds(t_mlx_helper *mlx_utils, int screen_x,
			int screen_y, int color)
{
	if (screen_x < SCREEN_WIDTH && screen_y < SCREEN_HEIGHT)
		mlx_put_pixel(mlx_utils->mini_map_img, screen_x, screen_y, color);
}

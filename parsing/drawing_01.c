/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:26:01 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 18:34:53 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	draw_tile_pixels(t_mlx_helper *mlx_utils,
			int map_x, int map_y, int color)
{
	int	py;
	int	px;
	int	screen_x;
	int	screen_y;

	py = 0;
	while (py < mlx_utils->tail - 1)
	{
		px = 0;
		while (px < mlx_utils->tail - 1)
		{
			screen_x = map_x * mlx_utils->tail + px;
			screen_y = map_y * mlx_utils->tail + py;
			draw_pixel_if_in_bounds(mlx_utils, screen_x, screen_y, color);
			px++;
		}
		py++;
	}
}

void	draw_map_row(t_utils *util, t_mlx_helper *mlx_utils, int map_y)
{
	int	map_width;
	int	map_x;
	int	color;

	map_width = strlen(util->map[map_y]);
	map_x = 0;
	while (map_x < map_width)
	{
		color = get_tile_color(util->map[map_y][map_x]);
		draw_tile_pixels(mlx_utils, map_x, map_y, color);
		map_x++;
	}
}

void	draw_map_(t_utils *util, t_mlx_helper *mlx_utils)
{
	int	map_height;
	int	map_y;

	map_height = lent(util->map);
	map_y = 0;
	while (map_y < map_height)
	{
		draw_map_row(util, mlx_utils, map_y);
		map_y++;
	}
}

void	draw_player(t_mlx_helper *mlx,
			int player_x, int player_y, int min_x, int min_y)
{
	int		player_size;
	float	player_screen_x;
	float	player_screen_y;
	int		py;
	int		px;
	int		screen_x;
	int		screen_y;

	player_size = 5;
	player_screen_x = mlx->minimap_x
		+ ((player_x - min_x) * mlx->minimap_scale);
	player_screen_y = mlx->minimap_y
		+ ((player_y - min_y) * mlx->minimap_scale);
	py = 0;
	while (py <= player_size)
	{
		px = 0;
		while (px <= player_size)
		{
			screen_x = player_screen_x + px;
			screen_y = player_screen_y + py;
			if (screen_x >= 0 && screen_x < mlx->minimap_size
				&& screen_y >= 0 && screen_y < mlx->minimap_size)
				mlx_put_pixel(mlx->mini_map_img,
					screen_x, screen_y, 0x43ff64cf);
			px++;
		}
		py++;
	}
}

void	clear_img(t_mlx_helper *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(mlx->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

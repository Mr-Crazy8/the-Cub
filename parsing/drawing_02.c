/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:39:07 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 17:41:03 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_img_mini_map(t_mlx_helper *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < mlx->minimap_size)
	{
		x = 0;
		while (x < mlx->minimap_size)
		{
			mlx_put_pixel(mlx->mini_map_img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_minimap_pixel(t_mlx_helper *mlx, int map_x, int map_y,
						int min_x, int min_y, int px, int py)
{
	int	screen_x;
	int	screen_y;
	int	color;

	screen_x = mlx->minimap_x + ((map_x - min_x) * mlx->minimap_scale) + px;
	screen_y = mlx->minimap_y + ((map_y - min_y) * mlx->minimap_scale) + py;
	if (screen_x >= 0 && screen_x < mlx->minimap_size
		&& screen_y >= 0 && screen_y < mlx->minimap_size)
	{
		color = get_minimap_tile_color(mlx->utils->map[map_y][map_x]);
		mlx_put_pixel(mlx->mini_map_img, screen_x, screen_y, color);
	}
}

void	draw_minimap_tile(t_mlx_helper *mlx, int map_x, int map_y,
			int min_x, int min_y)
{
	int	py;
	int	px;

	py = 0;
	while (py <= (int)mlx->minimap_scale - 1)
	{
		px = 0;
		while (px <= (int)mlx->minimap_scale - 1)
		{
			draw_minimap_pixel(mlx, map_x, map_y, min_x, min_y, px, py);
			px++;
		}
		py++;
	}
}

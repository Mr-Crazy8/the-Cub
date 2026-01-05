/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:39:07 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/05 18:03:37 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_img_mini_map(t_mlx_helper *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!mlx)
		return ;
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

void	draw_minimap_pixel(t_mlx_helper *mlx, t_minimap_pixel_params *params)
{
	int	screen_x;
	int	screen_y;
	int	color;

	if (!mlx || !params)
		return ; 
	screen_x = mlx->minimap_x + ((params->map_x - params->min_x)
			* mlx->minimap_scale) + params->px;
	screen_y = mlx->minimap_y + ((params->map_y - params->min_y)
			* mlx->minimap_scale) + params->py;
	if (screen_x >= 0 && screen_x < mlx->minimap_size
		&& screen_y >= 0 && screen_y < mlx->minimap_size)
	{
		color = get_minimap_tile_color(mlx->utils->map[params->map_y]
			[params->map_x]);
		mlx_put_pixel(mlx->mini_map_img, screen_x, screen_y, color);
	}
}

void	draw_minimap_tile(t_mlx_helper *mlx, t_minimap_tile_params *params)
{
	int						py;
	int						px;
	t_minimap_pixel_params	pixel_params;

	if (!mlx || !params)
		return;
	pixel_params.map_x = params->map_x;
	pixel_params.map_y = params->map_y;
	pixel_params.min_x = params->min_x;
	pixel_params.min_y = params->min_y;
	py = 0;
	while (py <= (int)mlx->minimap_scale - 1)
	{
		px = 0;
		while (px <= (int)mlx->minimap_scale - 1)
		{
			pixel_params.px = px;
			pixel_params.py = py;
			draw_minimap_pixel(mlx, &pixel_params);
			px++;
		}
		py++;
	}
}

void	draw_map_(t_utils *util, t_mlx_helper *mlx_utils)
{
	int	map_height;
	int	map_y;

	if (!util || !mlx_utils)
		return;
	map_height = lent(util->map);
	map_y = 0;
	while (map_y < map_height)
	{
		draw_map_row(util, mlx_utils, map_y);
		map_y++;
	}
}

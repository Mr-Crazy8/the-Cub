/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:20:19 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/03 20:13:58 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	calculate_minimap_bounds(t_mlx_helper *mlx, t_minimap_bounds *bounds)
{
	int	map_player_x;
	int	map_player_y;
	int	total_rows;

	if (!mlx || !bounds)
		exit(1);
	map_player_x = (int)mlx->player->pos_x;
	map_player_y = (int)mlx->player->pos_y;
	bounds->min_x = map_player_x - mlx->minimap_zone;
	bounds->max_x = map_player_x + mlx->minimap_zone;
	bounds->min_y = map_player_y - mlx->minimap_zone;
	bounds->max_y = map_player_y + mlx->minimap_zone;
	if (bounds->min_x < 0)
		bounds->min_x = 0;
	if (bounds->min_y < 0)
		bounds->min_y = 0;
	total_rows = 0;
	while (mlx->utils->map[total_rows])
		total_rows++;
	if (bounds->max_y > total_rows)
		bounds->max_y = total_rows;
}

int	get_row_length(char *row)
{
	int	length;
	
	if (!row)
		exit(1);
	length = 0;
	while (row[length])
		length++;
	return (length);
}

void	draw_minimap_row(t_mlx_helper *mlx, int map_y,
			t_minimap_bounds *bounds)
{
	int						row_length;
	int						current_max_x;
	int						map_x;
	t_minimap_tile_params	params;

	if (!mlx || !bounds)
		exit(1);
	row_length = get_row_length(mlx->utils->map[map_y]);
	current_max_x = bounds->max_x;
	if (current_max_x > row_length)
		current_max_x = row_length;
	params.map_y = map_y;
	params.min_x = bounds->min_x;
	params.min_y = bounds->min_y;
	map_x = bounds->min_x;
	while (map_x < current_max_x)
	{
		params.map_x = map_x;
		draw_minimap_tile(mlx, &params);
		map_x++;
	}
}

void	draw_minimap_grid(t_mlx_helper *mlx, t_minimap_bounds *bounds)
{
	int	map_y;

	if (!mlx || !bounds)
		exit(1);
	map_y = bounds->min_y;
	while (map_y < bounds->max_y)
	{
		if (!mlx->utils->map[map_y])
			break ;
		draw_minimap_row(mlx, map_y, bounds);
		map_y++;
	}
}

void	mini_map(t_mlx_helper *mlx)
{
	t_minimap_bounds		bounds;
	t_player_draw_params	params;

	if (!mlx)
		exit(1);
	clear_img_mini_map(mlx);
	calculate_minimap_bounds(mlx, &bounds);
	draw_minimap_grid(mlx, &bounds);
	params.player_x = (int)mlx->player->pos_x;
	params.player_y = (int)mlx->player->pos_y;
	params.min_x = bounds.min_x;
	params.min_y = bounds.min_y;
	draw_player(mlx, &params);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:20:19 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 18:25:05 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	calculate_minimap_bounds(t_mlx_helper *mlx, int *min_x, int *max_x,
			int *min_y, int *max_y)
{
	int	map_player_x;
	int	map_player_y;
	int	total_rows;

	map_player_x = (int)mlx->player->pos_x;
	map_player_y = (int)mlx->player->pos_y;
	*min_x = map_player_x - mlx->minimap_zone;
	*max_x = map_player_x + mlx->minimap_zone;
	*min_y = map_player_y - mlx->minimap_zone;
	*max_y = map_player_y + mlx->minimap_zone;
	if (*min_x < 0)
		*min_x = 0;
	if (*min_y < 0)
		*min_y = 0;
	total_rows = 0;
	while (mlx->utils->map[total_rows])
		total_rows++;
	if (*max_y > total_rows)
		*max_y = total_rows;
}

int	get_row_length(char *row)
{
	int	length;

	length = 0;
	while (row[length])
		length++;
	return (length);
}

void	draw_minimap_row(t_mlx_helper *mlx, int map_y, int min_x,
			int max_x, int min_y)
{
	int	row_length;
	int	current_max_x;
	int	map_x;

	row_length = get_row_length(mlx->utils->map[map_y]);
	current_max_x = max_x;
	if (current_max_x > row_length)
		current_max_x = row_length;
	map_x = min_x;
	while (map_x < current_max_x)
	{
		draw_minimap_tile(mlx, map_x, map_y, min_x, min_y);
		map_x++;
	}
}

void	draw_minimap_grid(t_mlx_helper *mlx, int min_x, int max_x,
			int min_y, int max_y)
{
	int	map_y;

	map_y = min_y;
	while (map_y < max_y)
	{
		if (!mlx->utils->map[map_y])
			break ;
		draw_minimap_row(mlx, map_y, min_x, max_x, min_y);
		map_y++;
	}
}

void	mini_map(t_mlx_helper *mlx)
{
	int	min_x;
	int	max_x;
	int	min_y;
	int	max_y;
	int	map_player_x;
	int	map_player_y;

	clear_img_mini_map(mlx);
	calculate_minimap_bounds(mlx, &min_x, &max_x, &min_y, &max_y);
	draw_minimap_grid(mlx, min_x, max_x, min_y, max_y);
	map_player_x = (int)mlx->player->pos_x;
	map_player_y = (int)mlx->player->pos_y;
	draw_player(mlx, map_player_x, map_player_y, min_x, min_y);
}

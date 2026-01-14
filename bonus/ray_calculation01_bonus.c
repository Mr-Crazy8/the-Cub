/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation01_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:25:09 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/12 22:26:05 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	calculate_draw_bounds(int *drawStart, int *drawEnd, int lineHeight)
{
	if (*drawStart < 0)
		*drawStart = 0;
	if (*drawEnd >= SCREEN_HEIGHT)
		*drawEnd = SCREEN_HEIGHT - 1;
}

void	calculate_wall_distance(t_mlx_helper *mlx_utils,
			t_player *player, int side)
{
	if (side == 0)
		mlx_utils->dist_to_wall = mlx_utils->dist_rayx - player->deltax;
	else
		mlx_utils->dist_to_wall = mlx_utils->dist_rayy - player->deltay;
}

void	process_single_ray(t_mlx_helper *mlx_utils, t_player *player, int x)
{
	int				side;
	int				did_we_hit_a_door;
	t_line_params	params;

	if (!mlx_utils || !player)
		return ;
	init_ray_direction(player, x);
	calculate_delta_dist(player);
	init_step_and_dist_x(mlx_utils, player);
	init_step_and_dist_y(mlx_utils, player);
	did_we_hit_a_door = 0;
	side = check_hit(mlx_utils, &did_we_hit_a_door);
	calculate_wall_distance(mlx_utils, player, side);
	params.x = x;
	params.side = side;
	params.did_we_hit_a_door = did_we_hit_a_door;
	draw_vertical_line(mlx_utils, player, &params);
}

void	calculate_texture_coords(t_texture_coords_params *params,
			t_texture_coord *coord)
{
	double	step_size;

	if (!params || !coord)
		return ;
	coord->tx = (int)(params->wx * (double)params->tex->width);
	step_size = (double)params->tex->height / (double)params->line_height;
	coord->ty = (int)((params->y - params->draw_start) * step_size);
	coord->tx = coord->tx % params->tex->width;
	coord->ty = coord->ty % params->tex->height;
}

int	get_texture_index(int side, int did_we_hit_a_door,
		double raydir_y, double raydir_x)
{
	if (side == 1)
		return (get_texture_index_vertical(did_we_hit_a_door, raydir_y));
	else
		return (get_texture_index_horizontal(did_we_hit_a_door, raydir_x));
}

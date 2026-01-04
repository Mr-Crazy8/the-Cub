/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_and_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:42:05 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/04 15:02:37 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_texture_index_vertical(int did_we_hit_a_door, double raydir_y)
{
	if (did_we_hit_a_door == 1)
		return (4);
	else if (raydir_y > 0)
		return (0);
	else
		return (1);
}

int	get_texture_index_horizontal(int did_we_hit_a_door, double raydir_x)
{
	if (did_we_hit_a_door == 1)
		return (4);
	else if (raydir_x > 0)
		return (3);
	else
		return (2);
}

static void	setup_wall_params(t_color_params *params, t_wall_x_params *wall)
{
	if (!params || !wall)
		exit(1);
	wall->side = params->side;
	wall->pos_x = params->pos_x;
	wall->pos_y = params->pos_y;
	wall->dist_to_wall = params->dist_to_wall;
	wall->raydir_x = params->raydir_x;
	wall->raydir_y = params->raydir_y;
}

static void	setup_tex_params(t_color_params *params, int tex_idx,
				double wx, t_texture_coords_params *tex)
{
	if (!params || !tex)
		exit(1);
	tex->tex = params->texture[tex_idx];
	tex->wx = wx;
	tex->y = params->y;
	tex->draw_start = params->draw_start;
	tex->line_height = params->line_height;
}

int	get_color(t_color_params *params)
{
	int						tex_idx;
	t_wall_x_params			wall;
	t_texture_coords_params	tex;
	t_texture_coord			coord;

	if (!params)
		exit(1);

	tex_idx = get_texture_index(params->side, params->did_we_hit_a_door,
			params->raydir_y, params->raydir_x);
	setup_wall_params(params, &wall);
	setup_tex_params(params, tex_idx, calculate_wall_x(&wall), &tex);
	calculate_texture_coords(&tex, &coord);
	return (((uint32_t *)params->texture[tex_idx]->pixels)
		[coord.ty * params->texture[tex_idx]->width + coord.tx]);
}

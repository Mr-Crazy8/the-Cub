/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_and_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:42:05 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 17:47:22 by anel-men         ###   ########.fr       */
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

int	get_texture_index(int side, int did_we_hit_a_door,
		double raydir_y, double raydir_x)
{
	if (side == 1)
		return (get_texture_index_vertical(did_we_hit_a_door, raydir_y));
	else
		return (get_texture_index_horizontal(did_we_hit_a_door, raydir_x));
}

void	calculate_texture_coords(mlx_texture_t *tex, double wx, int y,
			int drawStart, int lineHeight, int *tx, int *ty)
{
	double	step_size;

	*tx = (int)(wx * (double)tex->width);
	step_size = (double)tex->height / (double)lineHeight;
	*ty = (int)((y - drawStart) * step_size);
	*tx = *tx % tex->width;
	*ty = *ty % tex->height;
}

int	get_color(mlx_texture_t **texture, int side,
				double raydir_y, double raydir_x,
				int x, int y, double dist_to_wall, double pos_x, double pos_y,
				int lineHeight, int drawStart,
				int drawEnd, int did_we_hit_a_door)
{
	int			texture_index;
	double		wx;
	int			tx;
	int			ty;
	uint32_t	*pixels_32bit;

	texture_index = get_texture_index(side, did_we_hit_a_door,
			raydir_y, raydir_x);
	wx = calculate_wall_x(side, pos_x, pos_y, dist_to_wall, raydir_x, raydir_y);
	calculate_texture_coords(texture[texture_index],
		wx, y, drawStart, lineHeight, &tx, &ty);
	pixels_32bit = (uint32_t *)texture[texture_index]->pixels;
	return (pixels_32bit[ty * texture[texture_index]->width + tx]);
}

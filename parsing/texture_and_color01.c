/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_and_color01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:20:41 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 23:15:46 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_tile_color(char tile_type)
{
	if (tile_type == '1')
		return (0x8D5557);
	if (tile_type == '0')
		return (0x00b025);
	if (tile_type == 'D')
		return (0x00FF55);
	return (0x000000);
}

int	get_minimap_tile_color(char tile)
{
	if (tile == '1')
		return (0x8D5557);
	if (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'W' || tile == 'E')
		return (0x00b025);
	if (tile == 'D')
		return (0x00FF55);
	return (0x000000);
}

uint32_t	get_pixel_color(mlx_texture_t *texture, int x, int y)
{
	uint8_t		*pixel;
	uint32_t	color;

	pixel = &texture->pixels[(y * texture->width + x) * 4];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
	return (color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_and_color01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:20:41 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 17:21:25 by anel-men         ###   ########.fr       */
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

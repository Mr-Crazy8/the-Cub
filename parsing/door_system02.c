/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:36:24 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 18:34:37 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	load_door_texture(mlx_texture_t **texture)
{
	char	*door_path;

	if (!texture)
		return (0);

	door_path = "texture/doors.png";
	texture[4] = load_texture_with_check(door_path,
			"Error: Door texture failed to load\n");
	if (!texture[4])
		return (0);
	return (1);
}

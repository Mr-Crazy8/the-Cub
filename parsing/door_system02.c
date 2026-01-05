/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:36:24 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/05 18:01:23 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	load_door_texture(mlx_texture_t **texture)
{
	char	*door_path;

	if (!texture || !*texture)
		return;

	door_path = "texture/doors.png";
	texture[4] = load_texture_with_check(door_path,
			"the Door texture is not loading");
}

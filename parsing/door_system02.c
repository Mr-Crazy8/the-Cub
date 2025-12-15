/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:36:24 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/13 18:55:34 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	load_door_texture(mlx_texture_t **texture)
{
	char	*door_path;

	door_path = "/mnt/homes/anel-men/Desktop/the-Cub/doors.png";
	texture[4] = load_texture_with_check(door_path,
			"the Door texture is not loading");
}

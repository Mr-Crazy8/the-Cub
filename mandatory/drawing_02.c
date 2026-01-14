/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:39:07 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/12 18:10:32 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	clean_textures_in_case_error(mlx_texture_t **texture, int i)
{
	
	while (--i >= 0)
	{
		mlx_delete_texture(texture[i]);
		texture[i] = NULL;
	}
	return (0);
}

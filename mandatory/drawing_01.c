/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:26:01 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/09 11:42:00 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_img(t_mlx_helper *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!mlx)
		return ;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_put_pixel(mlx->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

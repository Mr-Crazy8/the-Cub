/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:56:36 by ayoakouh          #+#    #+#             */
/*   Updated: 2026/01/06 16:23:24 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	raycast(t_mlx_helper *mlx_utils, t_utils *utils, t_player *player)
{
	int	x;

	x = 0;
	if (!mlx_utils || !utils || !player)
		return ;
	clear_img(mlx_utils);
	while (x < SCREEN_WIDTH)
	{
		process_single_ray(mlx_utils, player, x);
		x++;
	}
}

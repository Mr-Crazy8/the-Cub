/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:56:36 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/12/11 16:03:17 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	raycast(t_mlx_helper *mlx_utils, t_utils *utils, t_player *player)
{
	int	x;

	x = 0;
	clear_img(mlx_utils);
	while (x < SCREEN_WIDTH)
	{
		process_single_ray(mlx_utils, player, x);
		x++;
	}
}

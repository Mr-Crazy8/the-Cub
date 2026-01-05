/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:47:56 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/05 18:36:27 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

t_mlx_helper	*init_mlx_helper(void)
{
	t_mlx_helper	*mlx_utils;

	mlx_utils = malloc(sizeof(t_mlx_helper));
	if (mlx_utils == NULL)
	{
		write(1, "malloc failed\n", 15);
	}
	return (mlx_utils);
}

void	init_mlx_images(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		return;
	mlx_utils->mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "ayoub", true);
	if (!mlx_utils->mlx_ptr)
		return;
	mlx_utils->mini_map_img = mlx_new_image(mlx_utils->mlx_ptr, 250, 250);
	mlx_utils->img = mlx_new_image(mlx_utils->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_utils->mlx_img = mlx_new_image(mlx_utils->mlx_ptr, 16, 16);
}

void	init_mlx_allocations(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		return ;
	mlx_utils->tail = 32;
	mlx_utils->player_place = malloc(2 * sizeof(int));
	if (!mlx_utils->player_place)
		{
			write(2, "Error\nMemory allocation failed\n", 31);
			return;
		}
	mlx_utils->map_h_w = malloc(2 * sizeof(int));
	if (!mlx_utils->map_h_w)
	{
		free(mlx_utils->player_place);
		mlx_utils->player_place = NULL;
		write(2, "Error\nMemory allocation failed\n", 31);
		return;
	}
}

void	setup_minimap_config(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		return;
	mlx_utils->minimap_size = 250;
	mlx_utils->minimap_x = 10;
	mlx_utils->minimap_y = 10;
	mlx_utils->minimap_zone = 10;
	mlx_utils->minimap_scale = (float)mlx_utils->minimap_size / (
			2.0 * mlx_utils->minimap_zone + 1.0);
}

void	setup_player(t_mlx_helper *mlx_utils, t_player *player, char helper)
{
	if (!mlx_utils || !player || !helper)
		return;
	find_h_w_for_map(mlx_utils->utils->map, mlx_utils->map_h_w);
	player->pos_y = mlx_utils->player_place[1] + 0.5;
	mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->mlx_img,
		(int)player->pos_x * mlx_utils->tail,
		(int)player->pos_y * mlx_utils->tail);
	check_derction_player(player, helper);
}

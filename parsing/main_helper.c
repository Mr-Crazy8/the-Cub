/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:47:56 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 21:04:38 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".MLX42.h"
#include "parsing.h"
#include "raycasting.h"
#include <stdlib.h>
void clean_mlx_helper(t_mlx_helper *mlx_utils);

t_mlx_helper	*init_mlx_helper(void)
{
	t_mlx_helper	*mlx_utils;

	mlx_utils = malloc(sizeof(t_mlx_helper));
	//mlx_utils = NULL; //segmentation fault
	if (mlx_utils == NULL)
	{
		write(1, "malloc failed\n", 15);
		return NULL;
	}
	mlx_utils->mlx_ptr = NULL;
    mlx_utils->img = NULL;
    mlx_utils->mini_map_img = NULL;
    mlx_utils->mlx_img = NULL;
    mlx_utils->texture = NULL;
    mlx_utils->sprit = NULL;
    mlx_utils->player_place = NULL;
    mlx_utils->map_h_w = NULL;
    mlx_utils->doors = NULL;
    mlx_utils->utils = NULL;
    mlx_utils->player = NULL;
	
	return (mlx_utils);
}

void helper_function_clean(t_mlx_helper *mlx_utils)
{
	if(!mlx_utils->mini_map_img)
	{
		mlx_terminate(mlx_utils->mlx_ptr);
		clean_up_utils(mlx_utils->utils);
		free(mlx_utils);
		exit(1);
	}
	if(!mlx_utils->img)
	{
		mlx_delete_image(mlx_utils->mlx_ptr, mlx_utils->mini_map_img);
		mlx_terminate(mlx_utils->mlx_ptr);
		clean_up_utils(mlx_utils->utils);
		free(mlx_utils);
		exit(1);
	}
	if(!mlx_utils->mlx_img)
	{
		mlx_delete_image(mlx_utils->mlx_ptr, mlx_utils->mini_map_img);
		mlx_delete_image(mlx_utils->mlx_ptr, mlx_utils->img);
		mlx_terminate(mlx_utils->mlx_ptr);
		clean_up_utils(mlx_utils->utils);
		free(mlx_utils);
		exit(1);
	}
}

void	init_mlx_images(t_mlx_helper *mlx_utils, t_utils *util)
{
	if (!mlx_utils)
	{
		clean_up_utils(util);
		exit(1);	
	}
	mlx_utils->mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D", true);
	if (!mlx_utils->mlx_ptr)
	{
		clean_up_utils(util);
		clean_mlx_helper(mlx_utils);
		exit(1);
	}
	mlx_utils->mini_map_img = mlx_new_image(mlx_utils->mlx_ptr, 250, 250);
	mlx_utils->img = mlx_new_image(mlx_utils->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_utils->mlx_img = mlx_new_image(mlx_utils->mlx_ptr, 16, 16);
	helper_function_clean(mlx_utils);
}

void	init_mlx_allocations(t_mlx_helper *mlx_utils, t_utils *util)
{
	if (!mlx_utils)
		(clean_up_utils(util) , exit(1));
	mlx_utils->tile = 32;
	mlx_utils->player_place = malloc(2 * sizeof(int));
	if (!mlx_utils->player_place)
	{
		write(2, "Error\nMemory allocation failed\n", 31);
		clean_up_utils(util);
		mlx_terminate(mlx_utils->mlx_ptr);
		exit(1);
	}
	mlx_utils->map_h_w = malloc(2 * sizeof(int));
	if (!mlx_utils->map_h_w)
	{
		clean_mlx_helper(mlx_utils);
		mlx_utils->player_place = NULL;
		clean_up_utils(util);
		write(2, "Error\nMemory allocation failed\n", 31);
		exit(1);
	}
}

void	setup_minimap_config(t_mlx_helper *mlx_utils)
{
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
	player->pos_x = mlx_utils->player_place[0] + 0.5;
	player->pos_y = mlx_utils->player_place[1] + 0.5;
	mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->mlx_img,
		(int)player->pos_x * mlx_utils->tile,
		(int)player->pos_y * mlx_utils->tile);
	check_derction_player(player, helper);
}

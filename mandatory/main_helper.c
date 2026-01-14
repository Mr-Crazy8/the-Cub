/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:47:56 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/14 13:39:06 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clean_mlx_helper(t_mlx_helper *mlx_utils);

t_mlx_helper	*init_mlx_helper(void)
{
	t_mlx_helper	*mlx_utils;

	mlx_utils = malloc(sizeof(t_mlx_helper));
	if (mlx_utils == NULL)
	{
		write(2, "Error\nmalloc failed\n", 21);
		return (NULL);
	}
	mlx_utils->mlx_ptr = NULL;
	mlx_utils->img = NULL;
	mlx_utils->mlx_img = NULL;
	mlx_utils->texture = NULL;
	mlx_utils->player_place = NULL;
	mlx_utils->map_h_w = NULL;
	mlx_utils->utils = NULL;
	mlx_utils->player = NULL;
	return (mlx_utils);
}

void	helper_function_clean(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils->img)
	{
		mlx_terminate(mlx_utils->mlx_ptr);
		clean_up_utils(mlx_utils->utils);
		clean_mlx_helper(mlx_utils);
		write(2, "Error\nmlx_utils->img failed\n", 29);
		exit(1);
	}
	if (!mlx_utils->mlx_img)
	{
		mlx_delete_image(mlx_utils->mlx_ptr, mlx_utils->img);
		mlx_terminate(mlx_utils->mlx_ptr);
		clean_up_utils(mlx_utils->utils);
		clean_mlx_helper(mlx_utils);
		write(2, "Error\nmlx_utils->mlx_img failed\n", 33);
		exit(1);
	}
}

void	init_mlx_images(t_mlx_helper *mlx_utils, t_utils *util)
{
	mlx_utils->mlx_ptr = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D", true);
	if (!mlx_utils->mlx_ptr)
	{
		clean_up_utils(util);
		clean_mlx_helper(mlx_utils);
		write(2, "Error\nmlx_utils->mlx_ptr failed\n", 33);
		exit(1);
	}
	mlx_utils->img = mlx_new_image(mlx_utils->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_utils->mlx_img = mlx_new_image(mlx_utils->mlx_ptr, 16, 16);
	helper_function_clean(mlx_utils);
}

void	init_mlx_allocations(t_mlx_helper *mlx_utils, t_utils *util)
{
	mlx_utils->tile = 32;
	mlx_utils->player_place = malloc(2 * sizeof(int));
	if (!mlx_utils->player_place)
	{
		write(2, "Error\nMemory allocation failed\n", 32);
		clean_up_utils(util);
		mlx_terminate(mlx_utils->mlx_ptr);
		clean_mlx_helper(mlx_utils);
		exit(1);
	}
	mlx_utils->map_h_w = malloc(2 * sizeof(int));
	if (!mlx_utils->map_h_w)
	{
		clean_mlx_helper(mlx_utils);
		mlx_utils->player_place = NULL;
		clean_up_utils(util);
		write(2, "Error\nMemory allocation failed\n", 32);
		exit(1);
	}
}

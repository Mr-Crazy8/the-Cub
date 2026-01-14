/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:00 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/14 13:24:51 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "raycasting.h"
#include <stdlib.h>
#include <unistd.h>

void	setup_mlx_hooks(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		return ;
	if (mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->img, 0, 0) == -1)
		return ;
	mlx_set_cursor_mode(mlx_utils->mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_loop_hook(mlx_utils->mlx_ptr, game_loop, mlx_utils);
}

void	init_core(char **av, t_mlx_helper **mlx_utils, t_utils **util, int argc)
{
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3d <map.cub>\n", 32);
		exit(1);
	}
	*util = parser(av[1]);
	if (!*util)
	{
		write(2, "Error\nParsing failed\n", 22);
		exit(1);
	}
	*mlx_utils = init_mlx_helper();
	if (!*mlx_utils)
	{
		clean_up_utils(*util);
		exit (1);
	}
}

int	init_game(t_utils *util, t_mlx_helper *mlx, t_player *player)
{
	char	helper;

	mlx->player = player;
	mlx->utils = util;
	mlx->texture = texture_loader(mlx);
	if (!mlx->texture)
		return (write(1, "Error\nFailed to load textures\n", 31),
			clean_up_utils(util),
			clean_mlx_helper(mlx), 1);
	init_mlx_images(mlx, util);
	init_mlx_allocations(mlx, util);
	helper = find_player(util->map, mlx->player_place);
	setup_player(mlx, player, helper);
	raycast(mlx, util, player);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_utils			*util;
	t_mlx_helper	*mlx_utils;
	t_player		player;

	init_core(argv, &mlx_utils, &util, argc);
	if (init_game(util, mlx_utils, &player))
		return (1);
	setup_mlx_hooks(mlx_utils);
	mlx_loop(mlx_utils->mlx_ptr);
	clean_mlx_helper(mlx_utils);
	clean_up_utils(util);
	return (0);
}

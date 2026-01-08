/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:00 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 17:58:23 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".MLX42.h"
#include "parsing.h"
#include "raycasting.h"
#include <stdlib.h>
#include <unistd.h>

t_sprite	*init_animation(t_mlx_helper *mlx_utils)
{
	t_sprite	*sprit;
	int			i;

	sprit = malloc(sizeof(t_sprite));
	if (!sprit)
		return (NULL);
	init_sprite_arrays(sprit);
	sprit->frame_delay = 10;
	sprit->frame_counter = 0;
	sprit->current_frame = 0;
	sprit->last_frame_time = mlx_get_time();
	if (load_sprite_frames(sprit) == 1)
		return (free(sprit), NULL);
	i = -1;
	while (++i < FIRE_FRAMES)
	{
		sprit->images[i] = mlx_texture_to_image(mlx_utils->mlx_ptr,
				&sprit->frames[i]->texture);
		if (!sprit->images[i])
			return (cleanup_failed_animation(mlx_utils, sprit, i), NULL);
	}
	return (sprit);
}

void	setup_mlx_hooks(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		return ;
	if (mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->img, 0, 0) == -1)
		return ;
	if (mlx_image_to_window(mlx_utils->mlx_ptr,
			mlx_utils->mini_map_img, 0, 0) == -1)
		return ;
	mini_map(mlx_utils);
	mlx_cursor_hook(mlx_utils->mlx_ptr, mouse_rotate_hook, mlx_utils);
	mlx_set_cursor_mode(mlx_utils->mlx_ptr, MLX_MOUSE_DISABLED);
	mlx_loop_hook(mlx_utils->mlx_ptr, game_loop, mlx_utils);
	mlx_loop_hook(mlx_utils->mlx_ptr, animation_loop, mlx_utils);
}

void	init_core(char **av, t_mlx_helper **mlx_utils, t_utils **util, int argc)
{
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3d <map.cub>\n", 31);
		exit(1);
	}
	*util = parser(av[1]);
	if (!*util)
	{
		write(2, "Error\nParsing failed\n", 21);
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
	init_mlx_images(mlx, util);
	init_mlx_allocations(mlx, util);
	setup_minimap_config(mlx);
	helper = find_player(util->map, mlx->player_place);
	setup_player(mlx, player, helper);
	mlx->texture = texture_loader(mlx);
	if (!mlx->texture)
		return (write(1, "Error\nFailed to load textures\n", 31),
			clean_up_utils(util),
			clean_mlx_helper(mlx), 1);
	update_doors_info(mlx);
	raycast(mlx, util, player);
	mlx->sprit = init_animation(mlx);
	if (!mlx->sprit)
		return (write(2, "Error\nFailed to load sprite animation\n", 39),
			clean_up_utils(util),
			clean_mlx_helper(mlx), 1);
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

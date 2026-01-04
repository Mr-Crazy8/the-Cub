/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:00 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/04 16:55:47 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <stdlib.h>

void	load_sprite_frames(t_sprite *sprit)
{
	if (!sprit)
		exit(1);
	sprit->frames[0] = mlx_load_xpm42("parsing/1.xpm42");
	sprit->frames[1] = mlx_load_xpm42("parsing/2.xpm42");
	sprit->frames[2] = mlx_load_xpm42("parsing/3.xpm42");
	sprit->frames[3] = mlx_load_xpm42("parsing/4.xpm42");
	sprit->frames[4] = mlx_load_xpm42("parsing/5.xpm42");
	sprit->frames[5] = mlx_load_xpm42("parsing/6.xpm42");
	sprit->frames[6] = mlx_load_xpm42("parsing/7.xpm42");
	sprit->frames[7] = mlx_load_xpm42("parsing/8.xpm42");
}

t_sprite	*init_animation(t_mlx_helper *mlx_utils)
{
	t_sprite	*sprit;
	int			i;

	if (!mlx_utils)
		exit(1);
	sprit = malloc(sizeof(t_sprite));
	if (!sprit)
		return (NULL);
	sprit->frame_delay = 10;
	sprit->frame_counter = 0;
	sprit->current_frame = 0;
	sprit->last_frame_time = mlx_get_time();
	load_sprite_frames(sprit);
	i = 0;
	while (i < FIRE_FRAMES)
	{
		sprit->images[i] = mlx_texture_to_image(mlx_utils->mlx_ptr,
				&sprit->frames[i]->texture);
		i++;
	}
	return (sprit);
}

void	setup_mlx_hooks(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		exit(1);
	mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->mini_map_img, 0, 0);
	mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->img, 0, 0);
	mini_map(mlx_utils);
	mlx_cursor_hook(mlx_utils->mlx_ptr, mouse_rotate_hook, mlx_utils);
	mlx_set_cursor_mode(mlx_utils->mlx_ptr, MLX_MOUSE_DISABLED);
	//mlx_key_hook(mlx_utils->mlx_ptr, handel_key, mlx_utils);
	mlx_loop_hook(mlx_utils->mlx_ptr, game_loop, mlx_utils);
	mlx_loop_hook(mlx_utils->mlx_ptr, animation_loop, mlx_utils);
}

void FUCK_YOU()
{
	system("leaks cub3d");
}

int	main(int argc, char *argv[])
{
	t_utils			*util;
	t_mlx_helper	*mlx_utils;
	t_player		player;
	char			helper;
	atexit(FUCK_YOU);
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3d <map.cub>\n", 31);
		return (1);
	}
	
	mlx_utils = init_mlx_helper(); // segmentation fault if mlx_utils is NULL [solve]

	if(!mlx_utils)
		exit(1);
	mlx_utils->player = &player;
	
	init_mlx_images(mlx_utils); // segmentation fault if mlx_utils is NULL [solve]
	init_mlx_allocations(mlx_utils);
	
	util = parser(argv[1]);

	if (!util)
	{
		exit(1);
	}
	mlx_utils->utils = util; // segmentation fault if util is NULL 
	setup_minimap_config(mlx_utils);
	helper = find_player(util->map, mlx_utils->player_place); // segmentation fault if util->map or mlx_utils->player_place  is NULL 
	setup_player(mlx_utils, &player, helper);  // segmentation fault if mlx_utils is NULL 
	mlx_utils->texture = texture_loader(mlx_utils); // segmentation fault if mlx_utils is NULL 
	update_doors_info(mlx_utils); // segmentation fault if mlx_utils is NULL 
	raycast(mlx_utils, util, &player); // segmentation fault if mlx_utils or player is NULL 
	mlx_utils->sprit = init_animation(mlx_utils); // segmentation fault if mlx_utils is NULL 
	setup_mlx_hooks(mlx_utils); // segmentation fault if mlx_utils is NULL 
	mlx_loop(mlx_utils->mlx_ptr);
}

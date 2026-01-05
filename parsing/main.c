/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:00 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/05 20:07:58 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".MLX42.h"
#include "parsing.h"
#include "raycasting.h"
#include <stdlib.h>
#include <unistd.h>


void clean_mlx_helper(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		return ;
	
	if (mlx_utils->texture)
	{
		int i;

		i = 0;
		while (i < 5)
		{
			if (mlx_utils->texture[i])
				mlx_delete_texture(mlx_utils->texture[i]);
			i++;
		}
		free(mlx_utils->texture);
	}

	if (mlx_utils->sprit)
	{
		int i;

		i = 0;

		while (i < FIRE_FRAMES)
		{
			if (mlx_utils->sprit->frames[i])
				mlx_delete_xpm42(mlx_utils->sprit->frames[i]);
			i++;
		}
		free(mlx_utils->sprit);
	}

	if (mlx_utils->mlx_ptr)
	{
		if (mlx_utils->mini_map_img)
			mlx_delete_image(mlx_utils->mlx_ptr, mlx_utils->mini_map_img);
		if (mlx_utils->img)
			mlx_delete_image(mlx_utils->mlx_ptr, mlx_utils->img);
		if (mlx_utils->mlx_img)
			mlx_delete_image(mlx_utils->mlx_ptr, mlx_utils->mlx_img);
		mlx_terminate(mlx_utils->mlx_ptr);
	}

	if (mlx_utils->player_place)
		free(mlx_utils->player_place);
	if (mlx_utils->map_h_w)
		free(mlx_utils->map_h_w);
	if (mlx_utils->doors)
		free(mlx_utils->doors);
	free(mlx_utils);
}

int	load_sprite_frames(t_sprite *sprit)
{

	sprit->frames[0] = mlx_load_xpm42("parsing/1.xpm42");
	if (!sprit->frames[0])
	{
		write(2, "Error:\nFailed to load parsing/1.xpm42", 38);
		return(1);
	}
	sprit->frames[1] = mlx_load_xpm42("parsing/2.xpm42");
	if (!sprit->frames[1])
	{
		write(2, "Error:\nFailed to load parsing/2.xpm42", 38);
		return(1);
	}
	sprit->frames[2] = mlx_load_xpm42("parsing/3.xpm42");
	if (!sprit->frames[2])
	{
		write(2, "Error:\nFailed to load parsing/3.xpm42", 38);
		return(1);
	}
	sprit->frames[3] = mlx_load_xpm42("parsing/4.xpm42");
	if (!sprit->frames[3])
	{
		write(2, "Error:\nFailed to load parsing/4.xpm42", 38);
		return(1);
	}
	sprit->frames[4] = mlx_load_xpm42("parsing/5.xpm42");
	if (!sprit->frames[4])
	{
		write(2, "Error:\nFailed to load parsing/5.xpm42", 38);
		return(1);
	}
	sprit->frames[5] = mlx_load_xpm42("parsing/6.xpm42");
	if (!sprit->frames[5])
	{
		write(2, "Error:\nFailed to load parsing/6.xpm42", 38);
		return(1);
	}
	sprit->frames[6] = mlx_load_xpm42("parsing/7.xpm42");
	if (!sprit->frames[6])
	{
		write(2, "Error:\nFailed to load parsing/7.xpm42", 38);
		return(1);
	}
	sprit->frames[7] = mlx_load_xpm42("parsing/8.xpm42");
	if (!sprit->frames[7])
	{
		write(2, "Error:\nFailed to load parsing/8.xpm42", 38);
		return(1);
	}
	return (0);
}

t_sprite	*init_animation(t_mlx_helper *mlx_utils)
{
	t_sprite	*sprit;
	int			i;


	sprit = malloc(sizeof(t_sprite));
	if (!sprit)
		return (NULL);
	sprit->frame_delay = 10;
	sprit->frame_counter = 0;
	sprit->current_frame = 0;
	sprit->last_frame_time = mlx_get_time();
	if(load_sprite_frames(sprit) == 1)
	{
		clean_up_utils(mlx_utils->utils);
		return (NULL);
	}
	i = 0;
	while (i < FIRE_FRAMES)
	{
		sprit->images[i] = mlx_texture_to_image(mlx_utils->mlx_ptr,
				&sprit->frames[i]->texture);
		if(!sprit->images[i])
		{
			mlx_delete_xpm42(sprit->frames[i]);
			free(sprit);
			return NULL;
		}
		i++;
	}
	return (sprit);
}

void	setup_mlx_hooks(t_mlx_helper *mlx_utils)
{
	if (!mlx_utils)
		return ;
	mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->mini_map_img, 0, 0);
	mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->img, 0, 0);
	mini_map(mlx_utils);
	
	mlx_cursor_hook(mlx_utils->mlx_ptr, mouse_rotate_hook, mlx_utils);
	mlx_set_cursor_mode(mlx_utils->mlx_ptr, MLX_MOUSE_DISABLED);
	
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
	
	util = parser(argv[1]);
	if (!util)
	{
		write(2, "Error\nParsing failed\n", 21);
		return 1;
	}
	
	mlx_utils = init_mlx_helper();
	if (!mlx_utils)
	{
		clean_up_utils(util);
		return 1;
	}
	
	mlx_utils->player = &player;
	mlx_utils->utils = util; 
	init_mlx_images(mlx_utils); 
	if (!mlx_utils->mlx_ptr)
	{
		free(mlx_utils);
		clean_up_utils(util);
		return (1);
	}

	init_mlx_allocations(mlx_utils);
	if (!mlx_utils || !mlx_utils->player_place || !mlx_utils->map_h_w)
	{
		if (mlx_utils->player_place)
			free(mlx_utils->player_place);
		if (mlx_utils->map_h_w)
			free(mlx_utils->map_h_w);
		mlx_terminate(mlx_utils->mlx_ptr);
		free(mlx_utils);
		clean_up_utils(util);
		clean_mlx_helper(mlx_utils);
		return (1);
	}
	
	setup_minimap_config(mlx_utils);
	helper = find_player(util->map, mlx_utils->player_place); 
	setup_player(mlx_utils, &player, helper);
	mlx_utils->texture = texture_loader(mlx_utils);
	update_doors_info(mlx_utils);
	raycast(mlx_utils, util, &player);
	mlx_utils->sprit = init_animation(mlx_utils);
	setup_mlx_hooks(mlx_utils);
	mlx_loop(mlx_utils->mlx_ptr);

	clean_mlx_helper(mlx_utils);
	clean_up_utils(util);
	return (0);
}

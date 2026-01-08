/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:50:53 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 22:41:05 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	find_h_w_for_map(char **map, int *map_h_w)
{
	int	i;
	int	j;
	int	r;

	if (!map || !*map)
		return ;
	j = 0;
	r = 0;
	i = lent(map) - 1;
	while (map[j])
	{
		r = 0;
		while (map[j][r])
			r++;
		j++;
	}
	map_h_w[0] = i;
	map_h_w[1] = r - 1;
}

void	cleanup_sprite(t_mlx_helper *mlx)
{
	int	i;

	i = -1;
	while (++i < FIRE_FRAMES)
	{
		if (mlx->mlx_ptr && mlx->sprit->images[i])
			mlx_delete_image(mlx->mlx_ptr, mlx->sprit->images[i]);
		if (mlx->sprit->frames[i])
			mlx_delete_xpm42(mlx->sprit->frames[i]);
	}
	free(mlx->sprit);
}

void	clean_mlx_helper(t_mlx_helper *mlx)
{
	if (!mlx)
		return ;
	if (mlx->texture)
		cleanup_textures(mlx);
	if (mlx->sprit)
		cleanup_sprite(mlx);
	if (mlx->mlx_ptr && mlx->mini_map_img)
		mlx_delete_image(mlx->mlx_ptr, mlx->mini_map_img);
	if (mlx->mlx_ptr && mlx->img)
		mlx_delete_image(mlx->mlx_ptr, mlx->img);
	if (mlx->mlx_ptr && mlx->mlx_img)
		mlx_delete_image(mlx->mlx_ptr, mlx->mlx_img);
	if (mlx->mlx_ptr)
		mlx_terminate(mlx->mlx_ptr);
	if (mlx->player_place)
		free(mlx->player_place);
	if (mlx->map_h_w)
		free(mlx->map_h_w);
	if (mlx->doors)
		free(mlx->doors);
	free(mlx);
}

int	cleanup_sprite_frames(t_sprite *sprit, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		if (sprit->frames[j])
			mlx_delete_xpm42(sprit->frames[j]);
		sprit->frames[j++] = NULL;
	}
	return (write(2, "Error:\nFailed to load sprite frame\n", 36), 1);
}

int	load_sprite_frames(t_sprite *sprit)
{
	char	*paths[FIRE_FRAMES];
	int		i;

	paths[0] = "mandatory/1.xpm42";
	paths[1] = "mandatory/2.xpm42";
	paths[2] = "mandatory/3.xpm42";
	paths[3] = "mandatory/4.xpm42";
	paths[4] = "mandatory/5.xpm42";
	paths[5] = "mandatory/6.xpm42";
	paths[6] = "mandatory/7.xpm42";
	paths[7] = "mandatory/8.xpm42";
	i = 0;
	while (i < FIRE_FRAMES)
	{
		sprit->frames[i] = mlx_load_xpm42(paths[i]);
		if (!sprit->frames[i])
			return (cleanup_sprite_frames(sprit, i));
		i++;
	}
	return (0);
}

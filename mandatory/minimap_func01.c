/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:50:53 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/14 12:36:03 by anel-men         ###   ########.fr       */
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

void	clean_mlx_helper(t_mlx_helper *mlx)
{
	if (!mlx)
		return ;
	if (mlx->texture)
		cleanup_textures(mlx);
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
	free(mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_and_input_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:14:18 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 23:14:12 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"
#include "raycasting_bonus.h"

void	game_loop(void *param)
{
	t_mlx_helper	*mlx;

	mlx = (t_mlx_helper *)param;
	if (!mlx)
		return ;
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_W))
		move_forward(mlx->player, mlx->utils->map, mlx);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_S))
		move_back(mlx->player, mlx->utils->map, mlx);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_A))
		move_right(mlx->player, mlx->utils->map, mlx);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_D))
		move_left(mlx->player, mlx->utils->map, mlx);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_LEFT))
		rotate_right(mlx->player, 0.1);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_RIGHT))
		rotate_left(mlx->player, 0.1);
	if (mlx_is_key_down(mlx->mlx_ptr, MLX_KEY_ESCAPE))
		(clean_up_utils(mlx->utils), clean_mlx_helper(mlx), exit(0));
	update_doors_info(mlx);
	clear_img(mlx);
	raycast(mlx, mlx->utils, mlx->player);
	mini_map(mlx);
}

void	mouse_rotate_hook(double xpos, double ypos, void *param)
{
	t_mlx_helper	*mlx;
	double			diff;
	double			rot;

	(void)ypos;
	mlx = (t_mlx_helper *)param;
	if (!mlx)
		return ;
	diff = xpos - (SCREEN_WIDTH / 2.0);
	if (fabs(diff) < 2.0)
		return ;
	rot = diff * 0.002;
	if (rot > 0)
		rotate_left(mlx->player, rot);
	else if (rot < 0)
		rotate_right(mlx->player, (rot * -1));
	mlx_set_mouse_pos(mlx->mlx_ptr, SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0);
}

int	count_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**fix_row_size(char **map)
{
	char	**normalized;
	int		max_len;
	int		row_count;
	int		i;

	if (!map || !*map)
		return (NULL);
	max_len = max_len_finder(map);
	if (max_len == 0)
		return (NULL);
	row_count = count_rows(map);
	normalized = malloc(sizeof(char *) * (row_count + 1));
	if (!normalized)
		return (NULL);
	i = 0;
	while (i < row_count)
	{
		normalized[i] = add_spaces(map[i], max_len);
		if (!normalized[i])
			return (free_normalized(normalized, i), NULL);
		i++;
	}
	normalized[row_count] = NULL;
	return (normalized);
}

t_utils	*init_utils(void)
{
	t_utils			*util;

	util = malloc(sizeof(t_utils));
	if (!util)
		return (NULL);
	util->c_color = NULL;
	util->f_color = NULL;
	util->no_path = NULL;
	util->so_path = NULL;
	util->ea_path = NULL;
	util->we_path = NULL;
	util->doors = NULL;
	util->total_doors = 0;
	util->map = NULL;
	util->file = NULL;
	util->c_color = malloc(3 * sizeof(int));
	if (!util->c_color)
		return (clean_up_utils(util), NULL);
	util->f_color = malloc(3 * sizeof(int));
	if (!util->f_color)
		return (clean_up_utils(util), NULL);
	return (util);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utiles03.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:37:45 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/14 16:57:44 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_door_info(t_doors_info *door, int x, int y)
{
	door->map_x = x;
	door->map_y = y;
	door->activation_distance = 2.0;
	door->state = 0;
	door->animation_progress = 0.0;
}

int	fill_doors_in_row(char *row, int row_y,
		t_doors_info *doors, int start_index)
{
	int	j;
	int	door_index;

	j = 0;
	door_index = start_index;
	while (row[j])
	{
		if (row[j] == 'D')
		{
			init_door_info(&doors[door_index], j, row_y);
			door_index++;
		}
		j++;
	}
	return (door_index);
}

t_doors_info	*allocate_doors_array(int count)
{
	t_doors_info	*doors;

	doors = malloc(sizeof(t_doors_info) * count);
	if (!doors)
		return (NULL);
	return (doors);
}

void	populate_doors_array(char **map, t_doors_info *doors)
{
	int	i;
	int	door_index;

	i = 0;
	door_index = 0;
	while (map[i])
	{
		door_index = fill_doors_in_row(map[i], i, doors, door_index);
		i++;
	}
}

t_doors_info	*extract_doors_info(t_utils *util)
{
	t_doors_info	*doors;
	int				total_doors;

	total_doors = count_total_doors(util->map);
	doors = allocate_doors_array(total_doors);
	if (!doors)
		return (NULL);
	populate_doors_array(util->map, doors);
	util->total_doors = total_doors;
	return (doors);
}

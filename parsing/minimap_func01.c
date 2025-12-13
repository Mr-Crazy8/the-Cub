/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_func01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:50:53 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 16:52:10 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	find_h_w_for_map(char **map, int *map_h_w)
{
	int	i;
	int	j;
	int	r;

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

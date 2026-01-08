/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_and_direction01_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:39:40 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:55:42 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	check_derction_player(t_player *player, char der)
{
	if (der == 'N')
		set_direction_north(player);
	else if (der == 'E')
		set_direction_east(player);
	else if (der == 'S')
		set_direction_south(player);
	else if (der == 'W')
		set_direction_west(player);
}

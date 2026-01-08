/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bonus_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:41 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:54:55 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"
#include <stdlib.h>

void	validate_space_neighbors(t_utils *util, unsigned long i,
			unsigned long j)
{
	if (!check_boundaries_exist(util, i, j))
		return ;
	if ((util->map[i][j + 1] != '1' && util->map[i][j + 1] != ' ') ||
		(util->map[i][j - 1] != '1' && util->map[i][j - 1] != ' ') ||
		(util->map[i - 1][j] != '1' && util->map[i - 1][j] != ' ') ||
		(util->map[i + 1][j] != '1' && util->map[i + 1][j] != ' '))
	{
		write(2, "Error\nthe Map is open 78\n", 23);
		clean_up_utils(util);
		exit(1);
	}
}

void	validate_zero_neighbors(t_utils *util, unsigned long i, unsigned long j)
{
	if (!check_boundaries_exist(util, i, j))
		return ;
	if (util->map[i][j + 1] == ' ' || util->map[i][j - 1] == ' ' ||
		util->map[i - 1][j] == ' ' || util->map[i + 1][j] == ' ')
	{
		write(2, "Error\nthe Map is open 1\n", 25);
		clean_up_utils(util);
		exit(1);
	}
}

void	process_map_character(t_utils *util, unsigned long i,
			unsigned long j, int *player)
{
	check_for_valid_character_in_map(util->map[i][j], util);
	if (is_player_char(util->map[i][j]))
		(*player)++;
	if (util->map[i][j] == ' ')
		validate_space_neighbors(util, i, j);
	else if (util->map[i][j] == '0')
		validate_zero_neighbors(util, i, j);
}

void	trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	pars_the_map(t_utils *util)
{
	unsigned long	i;
	unsigned long	j;
	int				player;

	i = 0;
	player = 0;
	while (util->map[i])
	{
		j = 0;
		while (util->map[i][j] == ' '
			|| (util->map[i][j] >= 9 && util->map[i][j] <= 13))
			j++;
		trim_newline(util->map[i]);
		while (util->map[i][j])
			(process_map_character(util, i, j, &player), j++);
		i++;
	}
	if (player != 1)
	{
		write(2, "Error\nThere more the one player\n", 33);
		clean_up_utils(util);
		exit(1);
	}
	pars_the_map_helper(util);
}

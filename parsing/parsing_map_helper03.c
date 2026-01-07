/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_helper03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:33 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 14:34:20 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	skip_leading_whitespace(char *line, int *j)
{
	while (line[*j] == ' ' || (line[*j] >= 9 && line[*j] <= 13))
		(*j)++;
}

int	trim_trailing_whitespace(char *line, int len)
{
	int	last_char;

	last_char = len - 1;
	if (last_char >= 0 && line[last_char] == '\n')
		last_char--;
	while (last_char >= 0 && (line[last_char] == ' '
			|| (line[last_char] >= 9 && line[last_char] <= 13)))
		last_char--;
	return (last_char);
}

void	validate_map_boundaries(char *line, int j, int last_char)
{
	if (line[j] != '1' || (last_char >= 0 && line[last_char] != '1'))
	{
		write(2, "Error\nthe Map is open 55\n", 26);
		return ;
	}
}

void	pars_the_map_helper(t_utils *util)
{
	int	i;
	int	j;
	int	len;
	int	last_char;

	i = 1;
	j = 0;

	while (util->map[i])
	{
		if (ft_strcmp(util->map[i], "\n") == 0)
		{
			i++;
			continue ;
		}
		j = 0;
		len = ft_strlen(util->map[i]);
		skip_leading_whitespace(util->map[i], &j);
		last_char = trim_trailing_whitespace(util->map[i], len);
		validate_map_boundaries(util->map[i], j, last_char);
		i++;
	}
	check_first_line(util->map, util);
	check_the_last_line(util->map, util);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

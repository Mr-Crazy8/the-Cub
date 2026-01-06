/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_helper02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:28 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 14:37:54 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
char **fix_row_size(char **map);
char *add_spaces(char *row, int target_len);
int max_len_finder(char **map);

void	extract_and_pars_the_map(t_utils *util, char **file)
{
	long long	map_start;
	int			total_lines;
	char 		**fixed_map;
	map_start = start_of_map(file);
	validate_map_start(map_start, util);
	total_lines = count_map_lines(file, map_start);
	util->map = extract_map_lines(file, map_start, total_lines, util);
	fixed_map = fix_row_size(util->map);
	if (!fixed_map)
	{	
		write(2, "Error\nFailed to normalize map rows\n", 35);
		return ;
	}
	free_string_array(util->map);
	util->map = fixed_map;
	pars_the_map(util);
}

void	check_for_valid_character_in_map(char str, t_utils *util)
{
	if (str != '0' && str != '1'
		&& str != 'N' && str != 'S' && str != 'D'
		&& str != 'E' && str != 'W' && str != ' ' && str != '\n')
	{
		write(2, "Error\nNon valid character in the map\n", 38);
		clean_up_utils(util);
		exit(2);
	}
}

void	check_first_line(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (str && str[i][j])
	{
		if (str[i][j] == '0' || str[i][j] == 'N'
			|| str[i][j] == 'S' || str[i][j] == 'E'
			|| str[i][j] == 'W' || str[i][j] == 'D')
		{
			write(2, "Error\nthe Map is open 2\n", 25);
			return ;
		}
		if (str[i][j] == ' ' && str[i + 1] && str[i + 1][j] == '0')
		{
			write(2, "Error\nthe Map is open 3\n", 25);
			return ;
		}
		j++;
	}
}

int	lent(char **str)
{
	int	i;

	i = 0;

	while (str && str[i])
		i++;
	return (i);
}

void	check_the_last_line(char **str)
{
	int	i;
	int	j;

	if (!str || !*str)
		exit(1);
	i = lent(str) - 1;
	j = 0;
	while (str && str[i] && str[i][j])
	{
		if (str[i][j] == '0' || str[i][j] == 'N'
			|| str[i][j] == 'S' || str[i][j] == 'E'
			|| str[i][j] == 'W' || str[i][j] == 'D')
		{
			write(2, "Error\nthe Map is open 66\n", 26);
			exit(2);
		}
		if (str[i][j] == ' ' && str[i - 1][j] == '0')
		{
			write(2, "Error\nthe Map is open 89\n", 26);
			exit(2);
		}
		j++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_helper02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:28 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/04 15:50:05 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	extract_and_pars_the_map(t_utils *util, char **file)
{
	long long	map_start;
	int			total_lines;

	if (!util || !file || !*file)
		exit(1);
	map_start = start_of_map(file); // segmentation fault if file is NULL
	validate_map_start(map_start);
	total_lines = count_map_lines(file, map_start); // segmentation fault if file is NULL
	util->map = extract_map_lines(file, map_start, total_lines); // segmentation fault if file is NULL
	pars_the_map(util); // segmentation fault if util is NULL
}

void	check_for_valid_character_in_map(char str)
{
	if (str != '0' && str != '1'
		&& str != 'N' && str != 'S' && str != 'D'
		&& str != 'E' && str != 'W' && str != ' ' && str != '\n')
	{
		write(2, "Error\nNon valid character in the map\n", 38);
		exit(2);
	}
}

void	check_first_line(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !*str)
		exit(1);
	while (str && str[i][j])
	{
		if (str[i][j] == '0' || str[i][j] == 'N'
			|| str[i][j] == 'S' || str[i][j] == 'E'
			|| str[i][j] == 'W' || str[i][j] == 'D')
		{
			write(2, "Error\nthe Map is open\n", 23);
			exit(2);
		}
		if (str[i][j] == ' ' && str[i + 1][j] == '0')
		{
			write(2, "Error\nthe Map is open\n", 23);
			exit(2);
		}
		j++;
	}
}

int	lent(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		exit(1);
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
			write(2, "Error\nthe Map is open\n", 23);
			exit(2);
		}
		if (str[i][j] == ' ' && str[i - 1][j] == '0')
		{
			write(2, "Error\nthe Map is open\n", 23);
			exit(2);
		}
		j++;
	}
}

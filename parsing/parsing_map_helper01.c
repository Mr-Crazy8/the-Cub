/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_helper01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:25 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 14:30:41 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_partial_map(char **map, int lines_allocated)
{
	int	j;

	j = 0;
	while (j < lines_allocated)
	{
		free(map[j]);
		j++;
	}
	free(map);
}

void	handle_strdup_error(char **map, int map_line)
{
	write(2, "Memory allocation failed\n", 25);
	free_partial_map(map, map_line);
}

void	copy_map_line(char **map, char *source, int map_line, t_utils *util)
{
	map[map_line] = ft_strdup(source);
	if (!map[map_line])
	{
		handle_strdup_error(map, map_line);
		clean_up_utils(util);
		exit(1);
	}
}

char	**extract_map_lines(char **file, long long map_start, int total_lines, t_utils *util)
{
	char	**map;
	int		map_line;
	int		i;

	map = allocate_map_array(total_lines);
	if (!map)
		(clean_up_utils(util), exit(1));
	i = map_start;
	map_line = 0;
	while (file[i] && map_line < total_lines)
	{
		copy_map_line(map, file[i], map_line, util);
		map_line++;
		i++;
	}
	map[map_line] = NULL;
	return (map);
}

void	validate_map_start(long long map_start, t_utils *util)
{
	if (map_start == -1)
	{
		write(2, "Error\nNo map found\n", 20);
		clean_up_utils(util);
		exit(2);
	}
}

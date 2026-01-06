/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:58 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 21:40:17 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parsing.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void free_string_array(char **array);

void clean_up_utils(t_utils *util)
{
	if (!util)
		return ;
	
	if (util->no_path)
		free(util->no_path);
	if (util->ea_path)
		free(util->ea_path);
	if (util->so_path)
		free(util->so_path);
	if (util->we_path)
		free(util->we_path);
	if (util->c_color)
		free(util->c_color);
	if (util->f_color)
		free(util->f_color);
	
	if (util->map)
		free_string_array(util->map);
	
	if (util->doors)
		free(util->doors);
	if (util->file)
		free_string_array(util->file);
		
	free(util);
}





void free_string_array(char **array)
{
	int i;
	
	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
int max_len_finder(char **map)
{
	int max_len;
	int current_len;
	int i;

	if (!map || !*map)
		return 0;
	
	max_len = 0;
	i = 0;
	while (map[i])
	{
		current_len = strlen(map[i]);
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

char *add_spaces(char *row, int target_len)
{
	char *padded;
	int current_len;
	int i;

	if (!row)
		return NULL;
	current_len = strlen(row);
	if (current_len >= target_len)
		return (ft_strdup(row));

	padded = malloc(target_len + 1);
	if (!padded)
		return NULL;
	i = 0;
	while (i < current_len)
	{
		padded[i] = row[i];
		i++;
	}

	while (i < target_len)
	{
		padded[i] = ' ';
		i++;
	}
	padded[target_len] = '\0';
	return padded;
}


char **fix_row_size(char **map)
{
	char **normalized;
	int max_len;
	int i;
	int row_count;
	
	if (!map || !*map)
		return NULL;
	max_len = max_len_finder(map);
	if (max_len == 0)
		return NULL;
	row_count = 0;
	while (map[row_count])
		row_count++;
	normalized = malloc(sizeof(char *) * (row_count + 1));
	if (!normalized)
		return NULL;
	
	i = 0;
	while (i < row_count)
	{
		normalized[i] = add_spaces(map[i], max_len);
		if (!normalized[i])
		{
			while (--i >= 0)
				free(normalized[i]);
			free(normalized);
			return (NULL);
		}
		i++;
	}
	normalized[row_count] = NULL;
	return normalized;
}
t_utils	*parser(char *str)
{
	t_utils			*util;
	int				fd;
	t_doors_info	*dors;
	
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
	char **fixed_map;
	util->c_color = malloc(3 * sizeof(int));
	if (!util->c_color)
		return (clean_up_utils(util), NULL);
	util->f_color = malloc(3 * sizeof(int));
	if (!util->f_color)
		return (clean_up_utils(util), NULL);
	fd = check_file(str);
	if (fd < 0)
		return (clean_up_utils(util), close(fd), NULL);
	util->file = read_file(fd, str);
	if (!util->file)
		return (close(fd) , clean_up_utils(util), NULL);
	
	extract_and_pars_the_texture(util, util->file);
	extract_and_pars_the_floor_and_ceiling_color(util, util->file);
	extract_and_pars_the_map(util, util->file);
	if (!util->map)
		return (clean_up_utils(util), NULL);
	util->doors = extract_doors_info(util);
	if (!util->doors && util->total_doors > 0)
		return (clean_up_utils(util), NULL);
	free_string_array(util->file);
	util->file = NULL;
	return (util);
}


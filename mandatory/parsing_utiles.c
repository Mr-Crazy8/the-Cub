/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:58 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/14 12:48:21 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clean_up_utils(t_utils *util)
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
	if (util->file)
		free_string_array(util->file);
	free(util);
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	max_len_finder(char **map)
{
	int	max_len;
	int	current_len;
	int	i;

	if (!map || !*map)
		return (0);
	max_len = 0;
	i = 0;
	while (map[i])
	{
		current_len = ft_strlen(map[i]);
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

char	*add_spaces(char *row, int target_len)
{
	char	*padded;
	int		current_len;
	int		i;

	if (!row)
		return (NULL);

	trim_newline(row);
	current_len = ft_strlen(row);
	if (current_len >= target_len)
		return (ft_strdup(row));
	padded = malloc(target_len + 1);
	if (!padded)
		return (NULL);
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
	return (padded);
}


int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int is_line_empty_or_spaces(const char *line)
{
	if (!line)
		return 1;
	while (*line)
	{
		if (!is_whitespace(*line))
			return 0;
		line++;
	}
	return 1;
}


void clean_file_trailing_space_or_newline(char **file)
{
	int i;

	if (!file)
		return;

	i = 0;
	while (file[i])
		i++;
	
	i--;
	while(i >= 0 && is_line_empty_or_spaces(file[i]))
	{
		free(file[i]);
		file[i] = NULL;
		i--;
	}
}
t_utils	*parser(char *str)
{
	t_utils			*util;
	int				fd;

	util = init_utils();
	if (!util)
		return (NULL);
	fd = check_file(str);
	if (fd < 0)
		return (clean_up_utils(util), close(fd), NULL);
	util->file = read_file(fd, str);
	if (!util->file)
		return (close(fd), clean_up_utils(util), NULL);
	clean_file_trailing_space_or_newline(util->file);
	extract_and_pars_the_texture(util, util->file);
	extract_and_pars_the_floor_and_ceiling_color(util, util->file);
	extract_and_pars_the_map(util, util->file);
	if (!util->map)
		return (clean_up_utils(util), NULL);
	(free_string_array(util->file), util->file = NULL);
	return (util);
}

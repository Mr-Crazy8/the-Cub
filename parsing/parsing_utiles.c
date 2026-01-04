/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:58 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/04 17:31:35 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include <stdlib.h>
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

t_utils	*parser(char *str)
{
	t_utils			*util;
	int				fd;
	t_doors_info	*dors;
	char			**file;

	util = malloc(sizeof(t_utils));
	if (!util)
		return (NULL);
	util->c_color = malloc(3 * sizeof(int));
	if (!util->c_color)
		return (free(util), NULL);
	util->f_color = malloc(3 * sizeof(int));
	if (!util->f_color)
		return (free(util->c_color), free(util), NULL);
	util->no_path = NULL;
	util->so_path = NULL;
	util->ea_path = NULL;
	util->we_path = NULL;
	util->doors = NULL;
	util->total_doors = 0;
	util->tile = 64;
	util->map = NULL;
	fd = check_file(str);
	if (fd < 0)
		return (clean_up_utils(util), NULL);
	file = read_file(fd, str);
	if (!file)
		return (close(fd) , clean_up_utils(util), NULL);
	
	extract_and_pars_the_texture(util, file);
	extract_and_pars_the_floor_and_ceiling_color(util, file);
	extract_and_pars_the_map(util, file);
	util->doors = extract_doors_info(util);

	free_string_array(file);
	close(fd);
	return (util);
}

void	print_config(t_utils *util)
{
	int	i;

	printf("NO TEXTURE : [%s]\n", util->no_path);
	printf("SO TEXTURE : [%s]\n", util->so_path);
	printf("WE TEXTURE : [%s]\n", util->we_path);
	printf("NO TEXTURE : [%s]\n", util->ea_path);
	printf("F COLORES : [%d] [%d] [%d]\n",
		util->f_color[0], util->f_color[1], util->f_color[2]);
	printf("C COLORES : [%d] [%d] [%d]\n",
		util->c_color[0], util->c_color[1], util->c_color[2]);
	i = 0;
	printf("Map :  \n");
	while (util->map[i])
	{
		printf("[%s]\n", util->map[i]);
		i++;
	}
}

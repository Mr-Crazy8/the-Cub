/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utiles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:58 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 16:14:05 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_utils	*parser(char *str)
{
	t_utils		*util;
	int			fd;
	doors_info	*dors;
	char		**file;

	util = malloc(sizeof(t_utils));
	util->c_color = malloc(3 * sizeof(int));
	util->f_color = malloc(3 * sizeof(int));
	util->no_path = NULL;
	util->so_path = NULL;
	util->ea_path = NULL;
	util->we_path = NULL;
	util->tile = 64;
	util->map = NULL;
	fd = check_file(str);
	file = read_file(fd, str);
	extract_and_pars_the_texture(util, file);
	extract_and_pars_the_floor_and_ceiling_color(util, file);
	extract_and_pars_the_map(util, file);
	util->doors = extract_doors_info(util);
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

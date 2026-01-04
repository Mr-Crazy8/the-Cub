/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture_helper01.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:50 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/04 16:09:46 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	check_duplicate(char *id, int done, char **texture)
{
	if (!texture || !*texture)
		exit(1);
	if (done == 1)
	{
		write(2, "Duplicate identifier\n", 22);
		free_split(texture);
		exit(2);
	}
}

void	handle_no_texture(t_utils *util, char **texture, t_texture_flags *flags)
{
	if (!util || !texture || !*texture || !flags)
		exit(1);
	check_duplicate("NO", flags->done_no, texture);
	util->no_path = ft_strdup(texture[1]);
	flags->done_no = 1;
	free_split(texture);
}

void	handle_so_texture(t_utils *util, char **texture, t_texture_flags *flags)
{
	if (!util || !texture || !*texture || !flags)
		exit(1);
	check_duplicate("SO", flags->done_so, texture);
	util->so_path = ft_strdup(texture[1]);
	flags->done_so = 1;
	free_split(texture);
}

void	handle_ea_texture(t_utils *util, char **texture, t_texture_flags *flags)
{
	if (!util || !texture || !*texture || !flags)
		exit(1);
	check_duplicate("EA", flags->done_ea, texture);
	util->ea_path = ft_strdup(texture[1]);
	flags->done_ea = 1;
	free_split(texture);
}

void	handle_we_texture(t_utils *util, char **texture, t_texture_flags *flags)
{
	if (!util || !texture || !*texture || !flags)
		exit(1);
	check_duplicate("WE", flags->done_we, texture);
	util->we_path = ft_strdup(texture[1]);
	flags->done_we = 1;
	free_split(texture);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture_bonus_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:54 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/09 00:14:42 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	handle_invalid_identifier(char **texture, t_utils *util)
{
	write(2, "Error\nNot Valide Identifier\n", 29);
	free_string_array(texture);
	clean_up_utils(util);
	exit(2);
}

void	process_texture_identifier(t_utils *util, char **texture,
								t_texture_flags *flags)
{
	if (ft_strcmp(texture[0], "NO") == 0)
		handle_no_texture(util, texture, flags);
	else if (ft_strcmp(texture[0], "SO") == 0)
		handle_so_texture(util, texture, flags);
	else if (ft_strcmp(texture[0], "EA") == 0)
		handle_ea_texture(util, texture, flags);
	else if (ft_strcmp(texture[0], "WE") == 0)
		handle_we_texture(util, texture, flags);
	else
		handle_invalid_identifier(texture, util);
}

void	process_texture_line(t_utils *util, char *line, t_texture_flags *flags)
{
	char	**texture;

	if (!is_texture_line(line))
		return ;
	texture = parse_texture_line(line);
	if (!texture)
	{
		clean_up_utils(util);
		exit(1);
	}
	process_texture_identifier(util, texture, flags);
}

void	extract_and_pars_the_texture(t_utils *util, char **file)
{
	t_texture_flags	flags;
	int				i;

	init_texture_flags(&flags);
	i = 0;
	while (file[i])
	{
		process_texture_line(util, file[i], &flags);
		i++;
	}
}

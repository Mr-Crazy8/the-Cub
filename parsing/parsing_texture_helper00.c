/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture_helper00.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:46 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 22:58:56 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	init_texture_flags(t_texture_flags *flags)
{
	flags->done_no = 0;
	flags->done_so = 0;
	flags->done_we = 0;
	flags->done_ea = 0;
}

int	is_texture_line(char *line)
{
	if (ft_strnstr(line, "./", ft_strlen(line)) == NULL)
		return (0);
	if (ft_strncmp(line, "NO", 2) == 0
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0)
		return (1);
	return (0);
}

char	**parse_texture_line(char *line)
{
	char	**texture;

	texture = ft_split(line, ' ');
	if (!texture)
		return (NULL);
	if (texture[1][ft_strlen(texture[1]) - 1] == '\n')
		texture[1][ft_strlen(texture[1]) - 1] = '\0';
	return (texture);
}

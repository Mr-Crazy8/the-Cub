/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_helper00_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:20 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/09 00:12:14 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i2;
	size_t	i1;
	size_t	r;
	size_t	len;
	char	*strtrim;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i1 = 0;
	i2 = ft_strlen(s1);
	r = 0;
	while (s1[i1] != '\0' && is_in_set(s1[i1], set))
		i1++;
	while (i2 > i1 && is_in_set(s1[i2 - 1], set))
		i2--;
	len = i2 - i1;
	strtrim = (char *)malloc((len + 1) * sizeof(char));
	if (strtrim == NULL)
		return (NULL);
	while (i1 < i2)
		strtrim[r++] = s1[i1++];
	strtrim[r] = '\0';
	return (strtrim);
}

long long	start_of_map(char **file)
{
	int	i;
	int	j;
	int	found_config;

	i = 0;
	j = 0;
	found_config = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || (file[i][j] >= 9 && file[i][j] <= 13))
			j++;
		if ((ft_strncmp(file[i] + j, "NO", 2) == 0
				|| ft_strncmp(file[i] + j, "SO", 2) == 0
				|| ft_strncmp(file[i] + j, "EA", 2) == 0
				|| ft_strncmp(file[i] + j, "WE", 2) == 0
				|| ft_strncmp(file[i] + j, "F", 1) == 0
				|| ft_strncmp(file[i] + j, "C", 1) == 0))
			found_config += 1;
		else if (found_config == 6
			&& file[i][j] != '\0' && file[i][j] != '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	count_map_lines(char **file, long long map_start)
{
	int	total_lines;
	int	i;

	total_lines = 0;
	i = map_start;
	while (file[i])
	{
		total_lines++;
		i++;
	}
	return (total_lines);
}

char	**allocate_map_array(int total_lines)
{
	char	**map;

	map = malloc(sizeof(char *) * (total_lines + 1));
	if (!map)
	{
		write(2, "Error\nMemory allocation failed\n", 32);
		return (NULL);
	}
	return (map);
}

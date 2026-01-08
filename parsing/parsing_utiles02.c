/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utiles02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:17:27 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 23:02:03 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	print_failed(void)
{
	write(2, "File doesn't exist or can't be opened\n", 39);
	return (-1);
}

int	count_lines(char *str)
{
	int		fd_2;
	char	*tmp;
	int		count;

	count = 0;
	fd_2 = open(str, O_RDONLY);
	if (fd_2 == -1)
		return (print_failed());
	tmp = get_next_line(fd_2);
	while (tmp != NULL)
	{
		free(tmp);
		count++;
		tmp = get_next_line(fd_2);
	}
	close(fd_2);
	return (count);
}

char	**read_file(int fd, char *str)
{
	char	**file;
	char	*line;
	int		lent;
	int		i;

	i = 0;
	lent = count_lines(str);
	if (lent < 0)
		return (NULL);
	file = malloc(sizeof(char *) * (lent + 1));
	if (!file)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		file[i] = ft_strdup(line);
		if (!file[i])
		{
			free(line);
			while (--i >= 0)
				free(file[i]);
			free(file);
			return (NULL);
		}
		free(line);
		i++;
		line = get_next_line(fd);
	}
	file[i] = NULL;
	close(fd);
	return (file);
}

int	count_doors_in_row(char *row)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (row[j])
	{
		if (row[j] == 'D')
			count++;
		j++;
	}
	return (count);
}

int	count_total_doors(char **map)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (map[i])
	{
		total += count_doors_in_row(map[i]);
		i++;
	}
	return (total);
}

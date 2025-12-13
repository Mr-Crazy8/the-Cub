/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utiles01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:14:33 by anel-men          #+#    #+#             */
/*   Updated: 2025/12/11 16:17:08 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	print_error(int fd)
{
	if (fd == -1)
	{
		write(2, "Texture file not found\n", 23);
		exit(2);
	}
	close(fd);
}

void	calculate_ray_direction(t_player *player, int screen_column,
		float *ray_dir_x, float *ray_dir_y)
{
	float	camera_x;

	camera_x = 2.0 * screen_column / (float)SCREEN_WIDTH - 1.0;
	*ray_dir_x = player->dir_x + player->plane_x * camera_x;
	*ray_dir_y = player->dir_y + player->plane_y * camera_x;
}

int	check_file(char *str)
{
	int		fd;
	size_t	len;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		write(2, "File doesn't exist or can't be opened\n", 39);
		exit(2);
	}
	len = strlen(str);
	if (len < 4 || strcmp(str + len - 4, ".cub") != 0)
	{
		write(2, "Not valid extension\n", 21);
		exit(2);
	}
	return (fd);
}

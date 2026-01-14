/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_system02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:36:24 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/14 12:53:37 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && (i + j) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	setup_player(t_mlx_helper *mlx_utils, t_player *player, char helper)
{
	find_h_w_for_map(mlx_utils->utils->map, mlx_utils->map_h_w);
	player->pos_x = mlx_utils->player_place[0] + 0.5;
	player->pos_y = mlx_utils->player_place[1] + 0.5;
	mlx_image_to_window(mlx_utils->mlx_ptr, mlx_utils->mlx_img,
		(int)player->pos_x * mlx_utils->tile,
		(int)player->pos_y * mlx_utils->tile);
	check_derction_player(player, helper);
}

int	check_collision_at(char **map, double x, double y, t_mlx_helper *mlx)
{
	double	margin;

	margin = 0.1;
	if (!mlx || !map || !*map)
		return (1);
	if (map[(int)(y - margin)][(int)(x - margin)] == '1' ||
		map[(int)(y - margin)][(int)(x + margin)] == '1' ||
		map[(int)(y + margin)][(int)(x - margin)] == '1' ||
		map[(int)(y + margin)][(int)(x + margin)] == '1')
		return (1);
	return (0);
}

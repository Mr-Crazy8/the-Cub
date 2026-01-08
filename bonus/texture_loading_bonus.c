/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:30:08 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:56:14 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	handle_texture_error(char *message)
{
	if (!message)
		write(1, message, 30);
}

mlx_texture_t	*load_texture_with_check(char *path, char *error_msg)
{
	mlx_texture_t	*texture;

	if (!path || !error_msg)
		return (NULL);
	texture = mlx_load_png(path);
	if (texture == NULL)
		return (handle_texture_error(error_msg), NULL);
	return (texture);
}

mlx_texture_t	**allocate_texture_array(void)
{
	mlx_texture_t	**texture;
	int				i;

	i = 0;
	texture = malloc(sizeof(mlx_texture_t *) * 5);
	if (texture == NULL)
	{
		write(1, "texture array malloc failed\n", 29);
		return (NULL);
	}
	while (i < 5)
	{
		texture[i] = NULL;
		i++;
	}
	return (texture);
}

int	load_wall_textures(mlx_texture_t **texture, t_utils *utils)
{
	if (!texture || !utils)
		return (0);
	texture[0] = load_texture_with_check(utils->no_path,
			"Error: NO texture failed to load\n");
	if (!texture[0])
		return (0);
	texture[1] = load_texture_with_check(utils->so_path,
			"Error: SO texture failed to load\n");
	if (!texture[1])
		return (clean_textures_in_case_error(texture, 1));
	texture[2] = load_texture_with_check(utils->ea_path,
			"Error: EA texture failed to load\n");
	if (!texture[2])
		return (clean_textures_in_case_error(texture, 2));
	texture[3] = load_texture_with_check(utils->we_path,
			"Error: WE texture failed to load\n");
	if (!texture[3])
		return (clean_textures_in_case_error(texture, 3));
	return (1);
}

mlx_texture_t	**texture_loader(t_mlx_helper *mlx_utils)
{
	mlx_texture_t	**texture;
	int				i;

	if (!mlx_utils || ! mlx_utils->utils)
		return (NULL);
	texture = allocate_texture_array();
	if (!texture)
		return (NULL);
	if (!load_wall_textures(texture, mlx_utils->utils))
		return (free(texture), NULL);
	if (!load_door_texture(texture))
	{
		i = 0;
		while (i < 4)
		{
			if (texture[i])
				mlx_delete_texture(texture[i]);
			i++;
		}
		free(texture);
		return (NULL);
	}
	return (texture);
}

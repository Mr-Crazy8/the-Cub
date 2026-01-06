/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:30:08 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/06 12:37:35 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	handle_texture_error(char *message)
{
	if(!message)
		exit(1);
	write(1, message, 30);
	exit(1);
}

mlx_texture_t	*load_texture_with_check(char *path, char *error_msg)
{
	mlx_texture_t	*texture;

	if (!path || !error_msg)
		exit(1);
	texture = mlx_load_png(path);
	if (texture == NULL)
		handle_texture_error(error_msg);
	return (texture);
}

mlx_texture_t	**allocate_texture_array(void)
{
	mlx_texture_t	**texture;

	texture = malloc(sizeof(mlx_texture_t *) * 5);
	if (texture == NULL)
	{
		write(1, "texture array malloc failed\n", 29);
		exit(1);
	}
	return (texture);
}

void	load_wall_textures(mlx_texture_t **texture, t_utils *utils)
{
	if (!texture || !utils)
	{
		printf("%p\n", utils);
		printf("%p\n", texture);
		printf("%p\n", *texture);
		printf("load_wall_textures\n");
		exit(1);
	}
	texture[0] = load_texture_with_check(utils->no_path,
			"the NO texture is not loading");
	texture[1] = load_texture_with_check(utils->so_path,
			"the SO texture is not loading");
	texture[2] = load_texture_with_check(utils->ea_path,
			"the EA texture is not loading");
	texture[3] = load_texture_with_check(utils->we_path,
			"the WE texture is not loading");
}

mlx_texture_t	**texture_loader(t_mlx_helper *mlx_utils)
{
	mlx_texture_t	**texture;

	if (!mlx_utils)
	{
		printf("texture_loader\n");
		exit(1);
	}
	texture = allocate_texture_array();
	load_wall_textures(texture, mlx_utils->utils);
	load_door_texture(texture);
	return (texture);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_system01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:22:29 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/07 14:53:25 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	draw_current_frame(t_mlx_helper *mlx, int x, int y)
{
	if (!mlx || !mlx->sprit || !mlx->sprit->images[mlx->sprit->current_frame])
		return ;
	mlx_image_to_window(mlx->mlx_ptr,
		mlx->sprit->images[mlx->sprit->current_frame],
		x,
		y);
}

void	animation_loop(void *param)
{
	t_mlx_helper	*mlx;
	static int		last_drawn = -1;
	int				x;
	int				y;

	mlx = (t_mlx_helper *)param;
	mlx = NULL;
	if (!mlx || !mlx->sprit)
		return ;
	if (!validate_animation_params(mlx))
		return ;
	update_animation(mlx->sprit);
	delete_previous_frame(mlx, last_drawn);
	ensure_current_frame_exists(mlx);
	calculate_sprite_position(mlx, &x, &y);
	draw_current_frame(mlx, x, y);
	last_drawn = mlx->sprit->current_frame;
}

static int	skip_whitespace_and_sing(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;
	long long	check;

	i = 0;
	res = 0;
	check = 0;
	sign = 1;
	i = skip_whitespace_and_sing(str, &sign);
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + (str[i] - '0');
		if (res / 10 != check)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		check = res;
		i++;
	}
	return ((int)(res * sign));
}

uint32_t    convert_rgba_to_int(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return ((r << 24) | (g << 16) | (b << 8) | a);
}
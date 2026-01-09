/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceiling_color_helper00_bo        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:06 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/09 00:09:39 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	check_if_in_range(int color, t_utils *util)
{
	if (!(color >= 0 && color <= 255))
	{
		write(2, "Error\nColor not in range [0-255]\n", 34);
		clean_up_utils(util);
		exit(1);
	}
}

int	is_valid_color_prefix(char c)
{
	return (c == 'F' || c == 'C');
}

int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	count_commas(char *file)
{
	int	i;
	int	counter;

	counter = 0;
	i = 1;
	i += skip_whitespace(&file[i]);
	while (file[i] && file[i] != '\n')
	{
		if (file[i] == ',')
			counter++;
		i++;
	}
	return (counter);
}

void	validate_comma_count(int counter, t_utils *util)
{
	if (counter != 2)
	{
		write(2, "Error\nNot Valide Color For Floor Or Ceiling\n", 45);
		clean_up_utils(util);
		exit(1);
	}
}

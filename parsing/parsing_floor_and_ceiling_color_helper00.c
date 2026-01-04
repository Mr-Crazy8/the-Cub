/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceiling_color_helper00.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:06 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/03 20:16:04 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_if_in_range(int color)
{
	if (!(color >= 0 && color <= 255))
	{
		write(2, "Error\nColor not in range [0-255]\n", 34);
		exit(2);
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
	if (!str)
		exit(1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	count_commas(char *file)
{
	int	i;
	int	counter;

	if (!file)
		exit(1);
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

void	validate_comma_count(int counter)
{
	if (counter != 2)
	{
		write(2, "not valide color for floor or ceiling\n", 39);
		exit(2);
	}
}

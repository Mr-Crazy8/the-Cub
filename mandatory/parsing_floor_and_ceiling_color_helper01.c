/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceiling_color_helper01.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:11 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/14 14:05:13 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**parse_and_validate_split(char *file, t_utils *util)
{
	char	**split;

	split = ft_split(file, ' ');
	if (!split || !split[0])
	{
		write(2, "Error\nInvalid color format\n", 28);
		clean_up_utils(util);
		free(file);
		exit(2);
	}
	return (split);
}

char	**parse_color_components(char **split, t_utils *util)
{
	char	**split1;

	split1 = ft_split(split[1], ',');
	if (!split1 || !split1[0] || !split1[1] || !split1[2])
	{
		free_string_array(split);
		write(2, "Error\nInvalid color format\n", 28);
		clean_up_utils(util);
		exit(2);
	}
	return (split1);
}


int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
		return (0);
}

 void check_is_full_numbers(char *number,  t_utils *util, char **split1)
{
	int i = 0;

	while (number[i])
	{
		if (ft_isalpha(number[i]))
		{
			clean_up_utils(util);
			write(2, "Error\nNot Valide number for the colors\n", 40);
			free_string_array(split1);
			exit(1);
		}
		i++;
	}
}

void	set_color_values(long long *color, char **split1, t_utils *util)
{
	check_is_full_numbers(split1[0], util, split1);
	color[0] = ft_atoi(split1[0]);
	check_if_in_range(color[0], util);
	check_is_full_numbers(split1[1], util, split1);
	color[1] = ft_atoi(split1[1]);
	check_if_in_range(color[1], util);
	check_is_full_numbers(split1[2], util, split1);
	color[2] = ft_atoi(split1[2]);
	check_if_in_range(color[2], util);
}

void	assign_color_to_util(t_utils *util, char type, char **split1)
{
	if (type == 'C')
		set_color_values(util->c_color, split1, util);
	else if (type == 'F')
		set_color_values(util->f_color, split1, util);
}

int	f_c_color_helpr(t_utils *util, char *file)
{
	char	**split;
	char	**split1;

	if (!is_valid_color_prefix(file[0]))
		return (0);
	validate_comma_count(count_commas(file), util, file);
	split = parse_and_validate_split(file, util);
	split1 = parse_color_components(split, util);
	free_string_array(split);
	assign_color_to_util(util, file[0], split1);
	free_string_array(split1);
	return (1);
}

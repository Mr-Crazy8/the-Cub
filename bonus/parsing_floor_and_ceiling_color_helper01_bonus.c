/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceiling_color_helper01_bo        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:11 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/08 20:54:52 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

char	**parse_and_validate_split(char *file, t_utils *util)
{
	char	**split;

	split = ft_split(file, ' ');
	if (!split || !split[1])
	{
		write(2, "Invalid color format\n", 21);
		clean_up_utils(util);
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
		write(2, "Invalid color format\n", 21);
		clean_up_utils(util);
		exit(2);
	}
	return (split1);
}

void	set_color_values(int *color, char **split1, t_utils *util)
{
	color[0] = ft_atoi(split1[0]);
	check_if_in_range(color[0], util);
	color[1] = ft_atoi(split1[1]);
	check_if_in_range(color[1], util);
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
	validate_comma_count(count_commas(file), util);
	split = parse_and_validate_split(file, util);
	split1 = parse_color_components(split, util);
	assign_color_to_util(util, file[0], split1);
	free_string_array(split);
	free_string_array(split1);
	return (1);
}

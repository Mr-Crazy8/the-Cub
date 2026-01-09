/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceiling_color_bonus.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:16 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/09 00:08:48 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	extract_and_pars_the_floor_and_ceiling_color(t_utils *util, char **file)
{
	int	i;
	int	done_f;
	int	done_c;

	i = 0;
	done_f = 0;
	done_c = 0;
	while (file[i])
	{
		if (file[i][0] == 'F' && done_f == 0)
		{
			f_c_color_helpr(util, file[i]);
			done_f = 1;
		}
		else if (file[i][0] == 'C' && done_c == 0)
		{
			f_c_color_helpr(util, file[i]);
			done_c = 1;
		}
		else if ((file[i][0] == 'F' && done_f == 1)
			|| (file[i][0] == 'C' && done_c == 1))
			(write(2, "Error\nDuplicate color identifier\n", 34),
				clean_up_utils(util), exit(2));
		i++;
	}
}

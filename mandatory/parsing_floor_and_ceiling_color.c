/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floor_and_ceiling_color.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:16 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/14 13:35:41 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>


void	extract_and_pars_the_floor_and_ceiling_color(t_utils *util, char **file)
{
	int	i;
	int	done_f;
	int	done_c;
	char *trim;

	i = 0;
	done_f = 0;
	done_c = 0;
	while (file[i])
	{
		trim = ft_strtrim(file[i], " ");
		if (!trim)
			(clean_up_utils(util), write(2, "Error\nft_strtrim failed\n", 25),exit(1));
		if (trim[0] == 'F' && done_f == 0)
		{
			if (trim[1] != ' ' && trim[1] != '\t') /// check this shit 
			{
				free(trim);
				write(2, "Error\nNot Valide color identifier\n", 34);
				clean_up_utils(util);
				exit(2);
			}
			f_c_color_helpr(util, trim);
			done_f = 1;
		}
		else if (trim[0] == 'C' && done_c == 0)
		{
			if (trim[1] != ' ' && trim[1] != '\t')
			{
				free(trim);
				write(2, "Error\nNot Valide color identifier\n", 34);
				clean_up_utils(util);
				exit(2);
			}
			f_c_color_helpr(util, trim);
			done_c = 1;
		}
		else if ((trim[0] == 'F' && done_f == 1)
			|| (trim[0] == 'C' && done_c == 1))
			(free(trim), write(2, "Error\nDuplicate color identifier\n", 34),
				clean_up_utils(util), exit(2));
		free(trim);
		i++;
	}
}

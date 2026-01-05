/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_helper04.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:48:37 by anel-men          #+#    #+#             */
/*   Updated: 2026/01/05 18:30:53 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_boundaries_exist(t_utils *util, unsigned long i, unsigned long j)
{
	return (util->map && util->map[i] && util->map[i][j] && i > 0 && j > 0 &&
			util->map[i + 1] != NULL && util->map[i][j + 1] != '\0' &&
			strlen(util->map[i - 1]) > j && strlen(util->map[i + 1]) > j);
}

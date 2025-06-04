/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comprobations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:50:53 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/04 13:00:36 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

int	is_wall_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_character_map(char **map, int lines)
{
	int	i;
	int	j;
	int	count_p;
	int	count_e;
	int	count_c;

	i = 0;
	count_p = 0;
	count_e = 0;
	count_c = 0;
	while (i < lines)
	{
		j = 0;
		while ((map[i][j] != '\0') && map[i][j] != '\n')
		{
			if (map[i][j] == 'P')
				count_p++;
			else if (map[i][j] == 'E')
				count_e++;
			else if (map[i][j] == 'C')
				count_c++;
			else if (map[i][j] != '1' && map[i][j] != '0')
				return (1);
			j++;
		}
		i++;
	}
	if (count_p != 1 || count_e != 1 || count_c < 1)
		return (1);
	return (0);
}

int	check_character_flood_fill(char **copy_map, int lines)
{
	int	i;
	int	j;
	int	count_e;
	int	count_c;

	i = 0;
	count_e = 0;
	count_c = 0;
	while (i < lines)
	{
		j = 0;
		while ((copy_map[i][j] != '\0') && copy_map[i][j] != '\n')
		{
			if (copy_map[i][j] == 'E')
				count_e++;
			else if (copy_map[i][j] == 'C')
				count_c++;
			j++;
		}
		i++;
	}
	if (count_e > 0 || count_c > 0)
		return (1);
	return (0);
}

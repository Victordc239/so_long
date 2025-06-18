/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:34:09 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/18 11:48:21 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

void	free_map(char **map, int lines)
{
	int	i;

	i = 0;
	while (i <= lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map_error(char **map, int lines)
{
	int i;

	i = 0;
	if (!map)
		return;
	while (i < lines)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
	free(map);
}

char	**copy(char **map, int lines)
{
	int		i;
	int		j;
	char	**copy_map;

	copy_map = malloc(sizeof(char *) * (lines + 1));
	if (!copy_map)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		copy_map[i] = ft_strdup(map[i]);
		if (!copy_map[i])
		{
			j = i - 1;
			while (j >= 0)
			{
				free(copy_map[j]);
				j--;
			}
			free(copy_map);
			return (NULL);
		}
		i++;
	}
	copy_map[lines] = NULL;
	return (copy_map);
}

void	flood_fill(char **copy_map, int x, int y, int lines)
{
	int	map_width;

	map_width = ft_strlen(copy_map[0]);
	if (x >= 0 && y >= 0 && y < lines && x < map_width && copy_map[y][x] != '1'
		&& copy_map[y][x] != 'F')
	{
		copy_map[y][x] = 'F';
		flood_fill(copy_map, x + 1, y, lines);
		flood_fill(copy_map, x - 1, y, lines);
		flood_fill(copy_map, x, y + 1, lines);
		flood_fill(copy_map, x, y - 1, lines);
	}
}

int	count_beer(char **map, int lines)
{
	int	count_c;
	int	i;
	int	j;

	i = 0;
	count_c = 0;
	while (i < lines)
	{
		j = 0;
		while ((map[i][j] != '\0') && map[i][j] != '\n')
		{
			if (map[i][j] == 'C')
				count_c++;
			j++;
		}
		i++;
	}
	return (count_c);
}

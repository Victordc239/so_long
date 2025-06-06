/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comprobations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:50:53 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/06 11:23:31 by vdiez-cu         ###   ########.fr       */
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

int	check_character_map(char **map, int lines, t_game *g)
{
	g->i = 0;
	g->count_p = 0;
	g->count_e = 0;
	g->count_c = 0;
	while (g->i < lines)
	{
		g->j = 0;
		while ((map[g->i][g->j] != '\0') && map[g->i][g->j] != '\n')
		{
			if (map[g->i][g->j] == 'P')
				g->count_p++;
			else if (map[g->i][g->j] == 'E')
				g->count_e++;
			else if (map[g->i][g->j] == 'C')
				g->count_c++;
			else if (map[g->i][g->j] != '1' && map[g->i][g->j] != '0')
				return (1);
			g->j++;
		}
		g->i++;
	}
	if (g->count_p != 1 || g->count_e != 1 || g->count_c < 1)
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

int	map_no_solution(t_game *g, int len_map)
{
	char	**copy_map;

	copy_map = copy(g->map, len_map);
	found_homer(g->map, len_map, &g->player_x, &g->player_y);
	flood_fill(copy_map, g->player_x, g->player_y, len_map);
	if (check_character_flood_fill(copy_map, len_map) == 1)
	{
		free_map(g->map, len_map);
		free_map(copy_map, len_map);
		return (write(1, "Error\nMap\n", 11), 1);
	}
	free_map(copy_map, len_map);
	return (0);
}

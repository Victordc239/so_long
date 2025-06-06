/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:50:51 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/06 13:07:29 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

void	found_homer(char **map, int lines, int *player_x, int *player_y)
{
	int	yy;
	int	xx;
	int	found;

	yy = 0;
	found = 0;
	while (yy < lines)
	{
		xx = 0;
		while (map[yy][xx] != '\0' && map[yy][xx] != '\n' && found != 1)
		{
			if (map[yy][xx] == 'P')
			{
				*player_x = xx;
				*player_y = yy;
				found = 1;
			}
			xx++;
		}
		yy++;
	}
}

void	exit_beer_homer(int old_x, int old_y, t_game *g)
{
	if (g->map[old_y][old_x] == 'E')
	{
		mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe,
			old_x * g->img_w, old_y * g->img_h);
	}
	else
	{
		mlx_put_image_to_window(g->mlx, g->win, g->img_cesped,
			old_x * g->img_w, old_y * g->img_h);
	}
	if (g->map[g->player_y][g->player_x] == 'E' && g->total_beers > 0)
	{
		mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe_homer,
			g->player_x * g->img_w, g->player_y * g->img_h);
	}
	else
	{
		mlx_put_image_to_window(g->mlx, g->win, g->img_homer,
			g->player_x * g->img_w, g->player_y * g->img_h);
	}
}

void	homer_drink_bar_homer(int keycode, int old_x, int old_y, t_game *g)
{
	int	x;
	int	y;

	x = old_x;
	y = old_y;
	if (g->map[y][x] == 'C')
	{
		g->total_beers--;
		g->map[y][x] = '0';
	}
	if ((((keycode == 100 || keycode == 65363) && g->map[y][x + 1] == 'E')
		|| ((keycode == 97 || keycode == 65361) && g->map[y][x - 1] == 'E')
		|| ((keycode == 115 || keycode == 65364) && g->map[y + 1][x] == 'E')
		|| ((keycode == 119 || keycode == 65362) && g->map[y - 1][x] == 'E'))
		&& g->total_beers == 0)
	{
		free_map(g->map, y + 1);
		exit(0);
	}
	exit_beer_homer(old_x, old_y, g);
}

int	homer_control_aux(int keycode, t_game *g, int x, int y)
{
	if ((keycode == 119 || keycode == 65362) && g->map[y - 1][x] != '1')
	{
		g->player_y--;
		return (1);
	}
	else if ((keycode == 115 || keycode == 65364) && g->map[y + 1][x] != '1')
	{
		g->player_y++;
		return (1);
	}
	else if ((keycode == 97 || keycode == 65361) && g->map[y][x - 1] != '1')
	{
		g->player_x--;
		return (1);
	}
	else if ((keycode == 100 || keycode == 65363) && g->map[y][x + 1] != '1')
	{
		g->player_x++;
		return (1);
	}
	return (0);
}

int	homer_control(int keycode, t_game *g)
{
	int	x;
	int	old_x;
	int	y;
	int	old_y;

	x = g->player_x;
	old_x = g->player_x;
	y = g->player_y;
	old_y = g->player_y;
	if (homer_control_aux(keycode, g, x, y) == 1)
	{
		print_movements(g);
	}
	else
		return (0);
	homer_drink_bar_homer(keycode, old_x, old_y, g);
	return (0);
}

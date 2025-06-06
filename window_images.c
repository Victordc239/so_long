/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:49:48 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/06 13:06:31 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

int	close_esc(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307)
		exit(0);
	return (0);
}

int	close_x(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	images(t_game *g)
{
	g->img_homer = mlx_xpm_file_to_image(g->mlx, "./textures/homer.xpm",
			&g->img_w, &g->img_h);
	g->img_arbusto = mlx_xpm_file_to_image(g->mlx, "./textures/arbusto.xpm",
			&g->img_w, &g->img_h);
	g->img_cesped = mlx_xpm_file_to_image(g->mlx, "./textures/cesped.xpm",
			&g->img_w, &g->img_h);
	g->img_duff = mlx_xpm_file_to_image(g->mlx, "./textures/duff.xpm",
			&g->img_w, &g->img_h);
	g->img_bar_moe = mlx_xpm_file_to_image(g->mlx, "./textures/bar_moe.xpm",
			&g->img_w, &g->img_h);
	g->img_bar_moe_homer = mlx_xpm_file_to_image(g->mlx,
			"./textures/bar_moe_homer.xpm", &g->img_w, &g->img_h);
	if (!g->img_homer || !g->img_arbusto || !g->img_cesped || !g->img_duff
		|| !g->img_bar_moe || !g->img_bar_moe_homer)
	{
		return (1);
	}
	return (0);
}

void	put_images_aux(t_game *g, int x, int y)
{
	if (g->map[y][x] == '1')
		mlx_put_image_to_window(g->mlx, g->win, g->img_arbusto,
			x * g->img_w, y * g->img_h);
	else if (g->map[y][x] == '0')
		mlx_put_image_to_window(g->mlx, g->win, g->img_cesped,
			x * g->img_w, y * g->img_h);
	else if (g->map[y][x] == 'C')
		mlx_put_image_to_window(g->mlx, g->win, g->img_duff,
			x * g->img_w, y * g->img_h);
	else if (g->map[y][x] == 'E')
		mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe,
			x * g->img_w, y * g->img_h);
	else if (g->map[y][x] == 'P')
	{
		mlx_put_image_to_window(g->mlx, g->win, g->img_homer,
			x * g->img_w, y * g->img_h);
		g->player_x = x;
		g->player_y = y;
	}
}

void	put_images(t_game *g, int len_map)
{
	int		x;
	int		y;

	y = 0;
	while (y < len_map)
	{
		x = 0;
		while (g->map[y][x] != '\0' && g->map[y][x] != '\n')
		{
			put_images_aux(g, x, y);
			x++;
		}
		y++;
	}
}

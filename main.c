/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:39 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/04 14:13:05 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

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

int	strlen_map(char *argv)
{
	char	*line;
	int		fd;
	int		count;

	count = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	free_map(char **map, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

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
	if ((((keycode == 100 || keycode == 65363) && g->map[y][x + 1] == 'E') || ((keycode == 97 || keycode == 65361) && g->map[y][x - 1] == 'E') || ((keycode == 115 || keycode == 65364) && g->map[y + 1][x] == 'E') || ((keycode == 119 || keycode == 65362) && g->map[y - 1][x] == 'E')) && g->total_beers == 0)
	{
		free_map(g->map, y + 1);
		exit(0);
	}
	if (g->map[old_y][old_x] == 'E')
		mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe, old_x * g->img_w, old_y * g->img_h);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->img_cesped, old_x * g->img_w, old_y * g->img_h);
	if (g->map[g->player_y][g->player_x] == 'E' && g->total_beers > 0)
		mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe_homer, g->player_x * g->img_w, g->player_y * g->img_h);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->img_homer, g->player_x * g->img_w, g->player_y * g->img_h);
}

void	print_movements(t_game *g)
{
	ft_putstr("Movements: ");
	g->count_movements++;
	ft_putnbr(g->count_movements);
	ft_putstr("\n");
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
	if ((keycode == 119 || keycode == 65362) && g->map[y - 1][x] != '1')
	{
		g->player_y--;
		print_movements(g);
	}
	else if ((keycode == 115 || keycode == 65364) && g->map[y + 1][x] != '1')
	{
		g->player_y++;
		print_movements(g);
	}
	else if ((keycode == 97 || keycode == 65361) && g->map[y][x - 1] != '1')
	{
		g->player_x--;
		print_movements(g);
	}
	else if ((keycode == 100 || keycode == 65363) && g->map[y][x + 1] != '1')
	{
		g->player_x++;
		print_movements(g);
	}
	else
		return (0);
	homer_drink_bar_homer(keycode, old_x, old_y, g);
	return (0);
}

void	flood_fill(char **copy_map, int x, int y, int lines, int map_width)
{
	if (x >= 0 && y >= 0 && y < lines && x < map_width && copy_map[y][x] != '1' && copy_map[y][x] != 'F')
	{
		copy_map[y][x] = 'F';
		flood_fill(copy_map, x + 1, y, lines, map_width);
		flood_fill(copy_map, x - 1, y, lines, map_width);
		flood_fill(copy_map, x, y + 1, lines, map_width);
		flood_fill(copy_map, x, y - 1, lines, map_width);
	}
}

char	**copy(char **map, int lines)
{
	int		i;
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
			while (i >= 0)
			{
				free(copy_map[i]);
				i--;
			}
			free(copy_map);
			return (NULL);
		}
		i++;
	}
	copy_map[lines] = NULL;
	return (copy_map);
}

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
			if (g->map[y][x] == '1')
				mlx_put_image_to_window(g->mlx, g->win, g->img_arbusto, x * g->img_w, y * g->img_h);
			else if (g->map[y][x] == '0')
				mlx_put_image_to_window(g->mlx, g->win, g->img_cesped, x * g->img_w, y * g->img_h);
			else if (g->map[y][x] == 'P')
			{
				mlx_put_image_to_window(g->mlx, g->win, g->img_homer, x * g->img_w, y * g->img_h);
				g->player_x = x;
				g->player_y = y;
			}
			else if (g->map[y][x] == 'C')
				mlx_put_image_to_window(g->mlx, g->win, g->img_duff, x * g->img_w, y * g->img_h);
			else if (g->map[y][x] == 'E')
				mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe, x * g->img_w, y * g->img_h);
			x++;
		}
		y++;
	}
}

int	load_map(int fd, char **map, int len_map, int *map_width)
{
	int		i;
	char	*line;
	int		i_line;

	i = 0;
	while (i < len_map)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free_map(map, i);
			return (close(fd), write(1, "Error\nlectura\n", 15), 1);
		}
		i_line = ft_strlen(line);
		if (line[i_line - 1] == '\n')
			i_line--;
		if (i == 0)
			*map_width = i_line;
		else if (i_line != *map_width)
		{
			free(line);
			free_map(map, i);
			return (close(fd), write(1, "Error\nRectangulo\n", 18), 1);
		}
		map[i] = line;
		if (line[0] != '1' || line[i_line - 1] != '1')
		{
			free_map(map, i);
			return (close(fd), write(1, "Error\nMuro Lateral\n", 20), 1);
		}
		i++;
	}
	if (is_wall_line(map[len_map - 1]) != 1 || is_wall_line(map[0]) != 1)
		return (free_map(map, i), close(fd), write(1, "Error\nMuros\n", 13), 1);
	return (close(fd), 0);
}

int	main(int argc, char *argv[])
{
	char	**copy_map;
	int		fd;
	int		len_map;
	int		map_width;
	t_game	g;

	g.count_movements = 0;
	g.player_x = 0;
	g.player_y = 0;
	if (argc != 2)
		return (write(1, "Error\n", 6), 1);
	len_map = strlen_map(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || len_map < 1)
		return (write(1, "Error\n", 6), 1);
	g.map = malloc(sizeof(char *) * (len_map + 1));
	if (g.map == NULL)
		return (write(1, "Error\nmalloc\n", 14), 1);
	if (load_map(fd, g.map, len_map, &map_width) != 0)
		return (1);
	close(fd);
	if (check_character_map(g.map, len_map) == 1)
	{
		free_map(g.map, len_map);
		return (write(1, "Error\ncaracteres\n", 18), 1);
	}
	g.mlx = mlx_init();
	if (g.mlx == NULL)
	{
		free_map(g.map, len_map);
		return (write(1, "Error\nminilibx\n", 16), 1);
	}
	copy_map = copy(g.map, len_map);
	found_homer(g.map, len_map, &g.player_x, &g.player_y);
	flood_fill(copy_map, g.player_x, g.player_y, len_map, map_width);
	if (check_character_flood_fill(copy_map, len_map) == 1)
	{
		free_map(g.map, len_map);
		return (write(1, "Error\nmapa de error\n", 21), 1);
	}
	g.win = mlx_new_window(g.mlx, map_width * 120, len_map * 120, "SO_LONG HOMER NO HOMERO");
	if (g.win == NULL)
	{
		free_map(g.map, len_map);
		return (write(1, "Error\nabrir ventana\n", 21), 1);
	}
	mlx_hook(g.win, 17, 0, close_x, NULL);
	mlx_key_hook(g.win, close_esc, NULL);
	g.img_homer = mlx_xpm_file_to_image(g.mlx, "./textures/homer.xpm", &g.img_w, &g.img_h);
	g.img_arbusto = mlx_xpm_file_to_image(g.mlx, "./textures/arbusto.xpm", &g.img_w, &g.img_h);
	g.img_cesped = mlx_xpm_file_to_image(g.mlx, "./textures/cesped.xpm", &g.img_w, &g.img_h);
	g.img_duff = mlx_xpm_file_to_image(g.mlx, "./textures/duff.xpm", &g.img_w, &g.img_h);
	g.img_bar_moe = mlx_xpm_file_to_image(g.mlx, "./textures/bar_moe.xpm", &g.img_w, &g.img_h);
	g.img_bar_moe_homer = mlx_xpm_file_to_image(g.mlx, "./textures/bar_moe_homer.xpm", &g.img_w, &g.img_h);
	if (!g.img_arbusto || !g.img_cesped || !g.img_homer || !g.img_duff || !g.img_bar_moe || !g.img_bar_moe_homer)
		return (write(1, "Error\ncargando imágenes\n", 25), 1);
	put_images(&g, len_map);
	g.total_beers = count_beer(g.map, len_map);
	mlx_hook(g.win, 2, 1, homer_control, &g);
	mlx_loop(g.mlx);
	free_map(g.map, len_map);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:39 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/03 14:08:54 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

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

int	check_character_copy_map(char **copy_map, int lines)
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
		ft_putstr("Movements: ");
		g->count_movements++;
		ft_putnbr(g->count_movements);
		ft_putstr("\n");
	}
	else if ((keycode == 115 || keycode == 65364) && g->map[y + 1][x] != '1')
	{
		g->player_y++;
		ft_putstr("Movements: ");
		g->count_movements++;
		ft_putnbr(g->count_movements);
		ft_putstr("\n");
	}
	else if ((keycode == 97 || keycode == 65361) && g->map[y][x - 1] != '1')
	{
		g->player_x--;
		ft_putstr("Movements: ");
		g->count_movements++;
		ft_putnbr(g->count_movements);
		ft_putstr("\n");
	}
	else if ((keycode == 100 || keycode == 65363) && g->map[y][x + 1] != '1')
	{
		g->player_x++;
		ft_putstr("Movements: ");
		g->count_movements++;
		ft_putnbr(g->count_movements);
		ft_putstr("\n");
	}
	else
		return (0);
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
	{
		mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe, old_x * g->img_w, old_y * g->img_h);
	}
	else
	{
		mlx_put_image_to_window(g->mlx, g->win, g->img_cesped, old_x * g->img_w, old_y * g->img_h);
	}
	if (g->map[g->player_y][g->player_x] == 'E' && g->total_beers > 0)
		mlx_put_image_to_window(g->mlx, g->win, g->img_bar_moe_homer, g->player_x * g->img_w, g->player_y * g->img_h);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->img_homer, g->player_x * g->img_w, g->player_y * g->img_h);
	return (0);
}

void	flood_fill(char **copy_map, int x, int y, int lines, int width)
{
	if (x >= 0 && y >= 0 && y < lines && x < width && copy_map[y][x] != '1' && copy_map[y][x] != 'F')
	{
		copy_map[y][x] = 'F';
		flood_fill(copy_map, x + 1, y, lines, width);
		flood_fill(copy_map, x - 1, y, lines, width);
		flood_fill(copy_map, x, y + 1, lines, width);
		flood_fill(copy_map, x, y - 1, lines, width);
	}
}

char	**make_copy(char **map, int lines)
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

int	main(int argc, char *argv[])
{
	char	*line;
	char	**map;
	char	**copy_map;
	int		fd;
	int		len_map;
	int		i;
	int		map_width;
	int		line_len;
	int		x;
	int		xx;
	int		y;
	int		yy;
	int		img_w;
	int		img_h;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_arbusto;
	void	*img_cesped;
	void	*img_homer;
	void	*img_duff;
	void	*img_bar_moe;
	void	*img_bar_moe_homer;
	t_game	g;

	i = 0;
	g.count_movements = 0;
	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	len_map = strlen_map(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || len_map < 1)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	map = malloc(sizeof(char *) * (len_map + 1));
	if (map == NULL)
	{
		write(1, "Error\nmalloc\n", 14);
		return (1);
	}
	while (i < len_map)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free_map(map, i);
			close(fd);
			write(1, "Error\nlectura\n", 15);
			return (1);
		}
		line_len = ft_strlen(line);
		if (line[line_len - 1] == '\n')
		{
			line_len--;
		}
		if (i == 0)
		{
			map_width = line_len;
		}
		else if (line_len != map_width)
		{
			free(line);
			free_map(map, i);
			close(fd);
			write(1, "Error\nRectangulo\n", 18);
			return (1);
		}
		map[i] = line;
		if (line[0] != '1' || line[line_len - 1] != '1')
		{
			free_map(map, i);
			close(fd);
			write(1, "Error\nMuro Lateral\n", 20);
			return (1);
		}
		i++;
	}
	close(fd);
	if (check_character_map(map, len_map) == 1)
	{
		write(1, "Error\ncaracteres\n", 18);
		free_map(map, len_map);
		return (1);
	}
	yy = 0;
	while (yy < len_map)
	{
		xx = 0;
		while (map[yy][xx] != '\0' && map[yy][xx] != '\n' && g.player_x == 0 && g.player_y == 0)
		{
			if (map[yy][xx] == 'P')
			{
				g.player_x = xx;
				g.player_y = yy;
			}
			xx++;
		}
		yy++;
	}
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
	{
		return (1);
	}
	copy_map = make_copy(map, len_map);
	flood_fill(copy_map, g.player_x, g.player_y, len_map, map_width);
	if (check_character_copy_map(copy_map, len_map) == 1)
	{
		write(1, "Error\nmapa de error\n", 21);
		return (1);
	}
	win_ptr = mlx_new_window(mlx_ptr, map_width * 120, len_map * 120, "SO_LONG HOMER QUE NO HOMERO");
	if (win_ptr == NULL)
	{
		return (1);
	}
	mlx_hook(win_ptr, 17, 0, close_x, NULL);
	mlx_key_hook(win_ptr, close_esc, NULL);
	img_homer = mlx_xpm_file_to_image(mlx_ptr, "./textures/homer.xpm", &img_w, &img_h);
	img_arbusto = mlx_xpm_file_to_image(mlx_ptr, "./textures/arbusto.xpm", &img_w, &img_h);
	img_cesped = mlx_xpm_file_to_image(mlx_ptr, "./textures/cesped.xpm", &img_w, &img_h);
	img_duff = mlx_xpm_file_to_image(mlx_ptr, "./textures/duff.xpm", &img_w, &img_h);
	img_bar_moe = mlx_xpm_file_to_image(mlx_ptr, "./textures/bar_moe.xpm", &img_w, &img_h);
	img_bar_moe_homer = mlx_xpm_file_to_image(mlx_ptr, "./textures/bar_moe_homer.xpm", &img_w, &img_h);
	if (!img_arbusto || !img_cesped || !img_homer || !img_duff || !img_bar_moe || !img_bar_moe_homer)
	{
		write(1, "Error\ncargando imágenes\n", 25);
		return (1);
	}
	y = 0;
	while (y < len_map)
	{
		x = 0;
		while (map[y][x] != '\0' && map[y][x] != '\n')
		{
			if (map[y][x] == '1')
			{
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_arbusto, x * img_w, y * img_h);
			}
			else if (map[y][x] == '0')
			{
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_cesped, x * img_w, y * img_h);
			}
			else if (map[y][x] == 'P')
			{
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_homer, x * img_w, y * img_h);
				g.player_x = x;
				g.player_y = y;
			}
			else if (map[y][x] == 'C')
			{
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_duff, x * img_w, y * img_h);
			}
			else if (map[y][x] == 'E')
			{
				mlx_put_image_to_window(mlx_ptr, win_ptr, img_bar_moe, x * img_w, y * img_h);
			}
			x++;
		}
		y++;
	}
	g.total_beers = count_beer(map, len_map);
	g.map = map;
	g.mlx = mlx_ptr;
	g.win = win_ptr;
	g.img_cesped = img_cesped;
	g.img_homer = img_homer;
	g.img_bar_moe = img_bar_moe;
	g.img_bar_moe_homer = img_bar_moe_homer;
	g.img_w = img_w;
	g.img_h = img_h;
	mlx_hook(win_ptr, 2, 1, homer_control, &g);
	mlx_loop(mlx_ptr);
	free_map(map, len_map);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:39 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/17 14:06:28 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

int	process_line(char *line, int *map_width, int i)
{
	int	i_line;

	i_line = ft_strlen(line);
	if (line[i_line - 1] == '\n')
		i_line--;
	if (i == 0)
		*map_width = i_line;
	else if (i_line != *map_width)
		return (1);
	return (0);
}

/*int	load_map(int fd, char **map, int len_map, int *map_width)
{
	int		i;
	char	*line;

	i = 0;
	while (i < len_map)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (free_map(map, i), close(fd),
				write(1, "Error\nread\n", 12), 1);
		if (process_line(line, map_width, i) != 0)
			return (free(line), free_map(map, i), close(fd),
				write(1, "Error\nRectangle\n", 17), 1);
		map[i] = line;
		if (line[0] != '1' || line[(ft_strlen(map[i])) - 2] != '1')
			return (free(line), free_map(map, i), close(fd),
				write(1, "Error\nSide Wall\n", 17), 1);
		i++;
	}
	while ((line = get_next_line(fd)) != NULL)
		free(line);
	if (is_wall_line(map[len_map - 1]) != 1 || is_wall_line(map[0]) != 1)
		return (free_map(map, i), close(fd), write(1, "Error\nWall\n", 12), 1);
	return (close(fd), 0);
}*/

int	load_map(int fd, char **map, int len_map, int *map_width)
{
	int	i;
	char	*line;

	i = 0;
	while (i < len_map)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			write(2, "DEBUG: GNL devolvió NULL\n", 25);
			return (free_map(map, i), close(fd),
				write(1, "Error\nread\n", 12), 1);
		}
		if (process_line(line, map_width, i) != 0)
			return (free(line), free_map(map, i), close(fd),
				write(1, "Error\nRectangle\n", 17), 1);
		map[i] = line;
		if (line[0] != '1' || line[ft_strlen(map[i]) - 2] != '1')
			return (free(line), free_map(map, i), close(fd),
				write(1, "Error\nSide Wall\n", 17), 1);
		i++;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
		write(2, "DEBUG: línea sobrante liberada\n", 31);
	}
	if (is_wall_line(map[len_map - 1]) != 1 || is_wall_line(map[0]) != 1)
		return (free_map(map, i), close(fd), write(1, "Error\nWall\n", 12), 1);
	return (close(fd), 0);
}

int	load_comprobations_map(char *ruta, t_game *g, int *len_map, int *map_width)
{
	int	fd;

	*len_map = strlen_map(ruta);
	fd = open(ruta, O_RDONLY);
	if (fd < 0 || *len_map < 1)
		return (write(1, "Error\n", 6), 1);
	g->map = malloc(sizeof(char *) * (*len_map + 1));
	if (!g->map)
		return (write(1, "Error\nmalloc\n", 14), 1);
	if (load_map(fd, g->map, *len_map, map_width) != 0)
	{
		return (1);
	}
	close(fd);
	if (check_character_map(g->map, *len_map, g) == 1)
	{
		free_map(g->map, *len_map);
		return (write(1, "Error\nCharacters\n", 18), 1);
	}
	return (0);
}

int	run(t_game *g, int len_map, int map_width)
{
	g->mlx = mlx_init();
	if (!g->mlx)
	{
		free_map(g->map, len_map);
		return (write(1, "Error\nMinilibx\n", 16), 1);
	}
	g->win = mlx_new_window(g->mlx, map_width * 120, len_map * 120, "SO_LONG");
	if (!g->win)
	{
		free_map(g->map, len_map);
		return (write(1, "Error\nOpen Window\n", 19), 1);
	}
	mlx_hook(g->win, 17, 0, close_x, NULL);
	mlx_key_hook(g->win, close_esc, NULL);
	if (images(g) == 1)
	{
		free_map(g->map, len_map);
		return (write(1, "Error\nLoad Images\n", 18), 1);
	}
	put_images(g, len_map);
	g->total_beers = count_beer(g->map, len_map);
	mlx_hook(g->win, 2, 1, homer_control, g);
	mlx_loop(g->mlx);
	free_map(g->map, len_map);
	return (0);
}

/*int	main(int argc, char *argv[])
{
	t_game	g;
	int		len_map;
	int		map_width;
	int		len_argv;

	g.count_movements = 0;
	g.player_x = 0;
	g.player_y = 0;
	if (argc != 2)
		return (write(1, "Error\n", 6), 1);
	len_argv = ft_strlen(argv[1]);
	if (ft_strncmp (argv[1] + len_argv - 4, ".ber", 4) != 0)
		return (write(1, "Error\nFile Type\n", 17), 1);
	if (load_comprobations_map(argv[1], &g, &len_map, &map_width) != 0)
		return (1);
	if (map_no_solution(&g, len_map) != 0)
		return (1);
	return (run(&g, len_map, map_width));
}*/

int	main(int argc, char *argv[])
{
	t_game	g;
	int		len_map;
	int		map_width;
	int		len_argv;
	char		*last_line;

	g.count_movements = 0;
	g.player_x = 0;
	g.player_y = 0;
	if (argc != 2)
		return (write(1, "Error\n", 6), 1);
	len_argv = ft_strlen(argv[1]);
	if (ft_strncmp(argv[1] + len_argv - 4, ".ber", 4) != 0)
		return (write(1, "Error\nFile Type\n", 17), 1);
	if (load_comprobations_map(argv[1], &g, &len_map, &map_width) != 0)
		return (1);
	if (map_no_solution(&g, len_map) != 0)
		return (1);
	last_line = get_next_line(-1);
	free(last_line);
	return (run(&g, len_map, map_width));
}

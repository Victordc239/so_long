/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:00 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/19 11:14:34 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img_homer;
	void	*img_floor;
	void	*img_bar_moe;
	void	*img_bar_moe_homer;
	void	*img_wall;
	void	*img_duff;
	int		img_w;
	int		img_h;
	int		player_x;
	int		player_y;
	int		count_movements;
	int		total_beers;
	int		count_p;
	int		count_e;
	int		count_c;
	int		j;
	int		i;
	int		strlen_map_struct;
	char	**map;
}			t_game;

int		is_wall_line(char *line);
int		close_game(t_game *g);
int		check_character_map(char **map, int lines, t_game *g);
int		check_character_flood_fill(char **copy_map, int lines);
int		strlen_map(char *argv);
int		close_esc(int keycode, void *param);
int		close_x(void *param);
int		homer_control(int keycode, t_game *g);
int		homer_control_aux(int keycode, t_game *g, int x, int y);
int		count_beer(char **map, int lines);
int		images(t_game *g);
int		map_no_solution(t_game *g, int len_map);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		process_line(char *line, int *map_width, int i);
int		load_map(int fd, char **map, int len_map, int *map_width);
int		run(t_game *g, int len_map, int map_width);
int		load_comprobations_map(char *argv, t_game *g, int *len_map,
			int *map_width);
void	free_map(char **map, int lines);
void	free_map_error(char **map, int lines);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
void	flood_fill(char **copy_map, int x, int y, int lines);
void	found_homer(char **map, int lines, int *player_x, int *player_y);
void	put_images(t_game *g, int len_map);
void	put_images_aux(t_game *g, int x, int y);
void	print_movements(t_game *g);
void	exit_beer_homer(int old_x, int old_y, t_game *g);
void	homer_drink_bar_homer(int keycode, int old_x, int old_y, t_game *g);
char	**copy(char **map, int lines);

#endif
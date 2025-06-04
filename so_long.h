/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:00 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/04 12:02:29 by vdiez-cu         ###   ########.fr       */
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
	void	*img_cesped;
	void	*img_bar_moe;
	void	*img_bar_moe_homer;
	void	*img_arbusto;
	void	*img_duff;
	int		img_w;
	int		img_h;
	int		player_x;
	int		player_y;
	int		count_movements;
	int		total_beers;
	char	**map;
}			t_game;

int		is_wall_line(char *line);
int		check_character_map(char **map, int lines);
int		check_character_flood_fill(char **copy_map, int lines);
int		strlen_map(char *argv);
int		close_esc(int keycode, void *param);
int		close_x(void *param);
int		homer_control(int keycode, t_game *g);
int		count_beer(char **map, int lines);
void	free_map(char **map, int lines);
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *s);
void	flood_fill(char **copy_map, int x, int y, int lines, int map_width);
void	found_homer(char **map, int lines, int *player_x, int *player_y);
void	put_images(t_game *g, int len_map);
char	**copy(char **map, int lines);

#endif
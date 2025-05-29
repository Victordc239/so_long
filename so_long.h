/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <victor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:00 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/05/29 22:52:25 by victor           ###   ########.fr       */
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
	void	*img_taberna_moe;
	int		img_w;
	int		img_h;
	int		player_x;
	int		player_y;
	int		count_movements;
	int		total_beers;
	char	**map;
}			t_game;

int		check_character_map(char **map, int lines);
int		is_wall_line(char *line);
int		strlen_map(char *argv);
int		close_esc(int keycode, void *param);
int		close_x(void *param);
int		homer_control(int keycode, t_game *g);
void	free_map(char **map, int lines);
void	ft_putnbr(int n);
void	ft_putchar(char c);
void	ft_putstr(char *s);

#endif
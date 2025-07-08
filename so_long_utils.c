/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:54:46 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/24 12:11:10 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include "./minilibx-linux/mlx.h"

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2", 1);
		ft_putnbr(147483648);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr(-n);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = n + '0';
		write(1, &c, 1);
	}
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
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
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	print_movements(t_game *g)
{
	ft_putstr("Movements: ");
	g->count_movements++;
	ft_putnbr(g->count_movements);
	ft_putstr("\n");
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((s1[i] != '\0') || (s2[i] != '\0')) && (s1[i] == s2[i]) && (i < n))
	{
		i++;
	}
	if (s1[i] == s2[i])
	{
		return (0);
	}
	else if (i < n)
	{
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	else
	{
		return (0);
	}
}

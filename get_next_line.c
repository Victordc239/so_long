/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:40:43 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/17 14:16:56 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_c_to_line(char **line, char c)
{
	char	*temp;
	char	char_buffer[2];

	char_buffer[0] = c;
	char_buffer[1] = '\0';
	if (*line == NULL)
		*line = ft_strdup("");
	temp = ft_strjoin(*line, char_buffer);
	free(*line);
	*line = temp;
}

int	process_rest_buffer(char **rest_buffer, char **line)
{
	size_t	i;
	char	*temp;

	i = 0;
	while ((*rest_buffer)[i] != '\n' && (*rest_buffer)[i] != '\0')
	{
		add_c_to_line(line, (*rest_buffer)[i]);
		i++;
	}
	if ((*rest_buffer)[i] == '\n')
	{
		add_c_to_line(line, '\n');
		temp = ft_strdup(*rest_buffer + i + 1);
		free(*rest_buffer);
		*rest_buffer = temp;
		return (1);
	}
	free(*rest_buffer);
	*rest_buffer = NULL;
	return (0);
}

char	*read_do_line(int fd, char *buffer, char **line, char **rest_buffer)
{
	int	i;
	int	n_chars;

	n_chars = read(fd, buffer, BUFFER_SIZE);
	while (n_chars > 0)
	{
		buffer[n_chars] = '\0';
		i = 0;
		while (buffer[i] != '\0')
		{
			if (buffer[i] != '\n')
				add_c_to_line(line, buffer[i]);
			else
			{
				add_c_to_line(line, '\n');
				*rest_buffer = ft_strdup(&buffer[i + 1]);
				return (free(buffer), *line);
			}
			i++;
		}
		n_chars = read(fd, buffer, BUFFER_SIZE);
	}
	if ((ft_strlen(*line) == 0) || (n_chars == -1))
		return (free(buffer), free(*line), NULL);	
	return (free(buffer), *line);
}

char	*get_next_line(int fd)
{
	static char	*rest_buffer;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	if (rest_buffer != NULL)
	{
		if (process_rest_buffer(&rest_buffer, &line) == 1)
			return (line);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));

	if (!buffer)
	{
		free(line); 
		return (NULL);
	}
	//if (!buffer)
	//	return (NULL);
	return (read_do_line(fd, buffer, &line, &rest_buffer));
}
/*
int	main(void)
{
	int	fd = open("quijote.txt", O_RDONLY);;
	char	*line = get_next_line(fd);

	while (line != 0)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/
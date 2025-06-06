/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:41:07 by vdiez-cu          #+#    #+#             */
/*   Updated: 2025/06/06 13:43:15 by vdiez-cu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[k] != '\0')
	{
		result[k] = s1[k];
		k++;
	}
	while (k < (ft_strlen(s1) + ft_strlen(s2)))
	{
		result[k] = s2[i];
		k++;
		i++;
	}
	result[k] = '\0';
	return (result);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	i;
	size_t	size_s;
	char	*aux;

	aux = (char *)s;
	i = 0;
	size_s = ft_strlen(aux);
	result = (char *)malloc(sizeof(char) * size_s + 1);
	if (!result)
		return (NULL);
	while (aux[i] != '\0')
	{
		result[i] = aux[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(const char *str, int c)
{
	size_t			i;
	unsigned char	new_c;

	if (c < 0 || c > 255)
		new_c = (unsigned char)(c % 256);
	else
		new_c = (unsigned char)c;
	i = 0;
	while ((unsigned char)str[i] != '\0')
	{
		if ((unsigned char)str[i] == new_c)
			return ((char *)&str[i]);
		i++;
	}
	if (c == '\0' || new_c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

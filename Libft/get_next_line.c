/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:50:57 by britela-          #+#    #+#             */
/*   Updated: 2026/04/06 22:34:41 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char *str)
{
	if (str != NULL)
	{
		free(str);
	}
}

char	*ft_rest(char *str)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		ft_free(str);
		return (NULL);
	}
	i++;
	rest = malloc(sizeof(char) * ft_strlen(str) - i + 1);
	if (rest == NULL)
		return (NULL);
	while (str[i] != '\0')
		rest[j++] = str[i++];
	rest[j] = '\0';
	ft_free(str);
	return (rest);
}

char	*ft_check_word(char *str)
{
	int		i;
	char	*newword;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
	{
		i++;
	}
	newword = ft_substr(str, 0, i);
	return (newword);
}

char	*ft_read(int fd, char *word, char *conc)
{
	ssize_t	i;
	char	*position;

	i = 1;
	position = ft_strchr(conc, '\n');
	while (position == NULL && i > 0)
	{
		i = read(fd, word, BUFFER_SIZE);
		if (i < 0)
		{
			return (NULL);
		}
		word[i] = '\0';
		conc = ft_strjoin(conc, word);
		position = ft_strchr(conc, '\n');
	}
	return (conc);
}

char	*get_next_line(int fd)
{
	char		*word;
	char		*line;
	static char	*conc;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd != 3)
		return (NULL);
	word = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (word == NULL)
		return (NULL);
	conc = ft_read(fd, word, conc);
	ft_free(word);
	if (conc == NULL || conc[0] == '\0')
	{
		ft_free(conc);
		conc = NULL;
		return (NULL);
	}
	line = ft_check_word(conc);
	conc = ft_rest(conc);
	return (line);
}
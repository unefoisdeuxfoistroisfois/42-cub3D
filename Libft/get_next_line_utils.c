/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:54:06 by britela-          #+#    #+#             */
/*   Updated: 2026/04/06 19:01:37 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;
	char	*str;
	int		i;

	if (s == NULL)
		return (NULL);
	cc = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == cc)
		{
			return (&str[i]);
		}
		i++;
	}
	if (cc == '\0')
	{
		return (&str[i]);
	}
	return (NULL);
}

char	*ft_empty(void)
{
	char	*newword;

	newword = malloc(sizeof(char) * 1);
	if (newword == NULL)
	{
		return (NULL);
	}
	newword[0] = '\0';
	return (newword);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*newword;
	unsigned int		sizes;
	size_t				i;
	size_t				j;

	if (s == NULL)
		return (NULL);
	sizes = ft_strlen(s);
	if (start >= sizes)
		return (ft_empty());
	if (len > sizes - start)
		len = sizes - start;
	newword = malloc(sizeof(char) * (len + 1));
	if (newword == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (j < len)
	{
		newword[j] = s[i];
		j++;
		i++;
	}
	newword[j] = '\0';
	return (newword);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newword;
	int		i;
	int		j;

	if (s1 == NULL)
	{
		s1 = ft_empty();
	}
	newword = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (newword == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		newword[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		newword[i++] = s2[j++];
	newword[i] = '\0';
	ft_free(s1);
	return (newword);
}
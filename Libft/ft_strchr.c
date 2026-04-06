/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: britela- <britela-@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:34:55 by britela-          #+#    #+#             */
/*   Updated: 2026/04/06 22:44:44 by britela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
int	main()
{
	char *mot;
	char	lettre;
	char	*res;

	mot = "Bradley";
	lettre = '\0';

	res = ft_strchr(mot, lettre);
	printf("%s", res);
	return (0);
}*/

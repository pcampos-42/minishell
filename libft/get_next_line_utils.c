/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:12:25 by rafernan          #+#    #+#             */
/*   Updated: 2022/05/04 13:49:18 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;

	if (s)
	{
		tmp = (char *)(s);
		while (*tmp)
		{
			if (*tmp == (char)c)
				return (tmp);
			tmp++;
		}
		if (*tmp == c)
			return (tmp);
	}
	return (NULL);
}

void	*ft_memcpy(const void *dst, const void *src, size_t n)
{
	char	*dstptr;
	char	*srcptr;

	dstptr = (char *)(dst);
	srcptr = (char *)(src);
	if (dstptr && srcptr)
	{
		while (n--)
			*dstptr++ = *srcptr++;
	}
	return ((void *)dst);
}

size_t	new_strlen(const char *s)
{
	int		i;
	char	*cp;

	i = 0;
	cp = (char *)(s);
	while (cp && *cp)
	{
		cp++;
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;

	if (s)
	{
		len = new_strlen(s);
		if (!len)
			return (NULL);
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		ft_memcpy(str, s, len);
		*(str + len) = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1len;
	size_t	s2len;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	s1len = new_strlen(s1);
	s2len = new_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, s1len);
	ft_memcpy(ptr + s1len, s2, s2len);
	ptr[s1len + s2len] = '\0';
	return (ptr);
}

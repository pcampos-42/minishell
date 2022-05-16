/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:14:37 by lucas-ma          #+#    #+#             */
/*   Updated: 2021/10/22 09:16:59 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_issep(char s, char c)
{
	return (s == c || s == '\0');
}

static int	countwords(char const *s, char c)
{
	int	index;
	int	words;

	index = 0;
	words = 0;
	while (s[index] != '\0')
	{
		if (ft_issep(s[index], c) == 0 && ft_issep(s[index + 1], c) == 1)
			words++;
		index++;
	}
	return (words);
}

static void	ft_cpywords(char *dest, char *src, char c)
{
	int	index;

	index = 0;
	while (ft_issep(src[index], c) == 0)
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
}

static void	do_the_split(char **matriz, char *s, char c)
{
	int		i;
	int		j;
	int		word;
	char	*str;

	i = 0;
	word = 0;
	str = s;
	while (s[i] != '\0')
	{
		if (ft_issep(s[i], c) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_issep(str[i + j], c) == 0)
				j++;
			matriz[word] = malloc((j + 1) * sizeof(char));
			if (!matriz[word])
				return ;
			ft_cpywords(matriz[word], str + i, c);
			i += j;
			word++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**matriz;
	int		words;

	if (!s)
		return (NULL);
	words = countwords(s, c);
	matriz = malloc((words + 1) * sizeof(char *));
	if (!matriz)
		return (NULL);
	matriz[words] = NULL;
	do_the_split(matriz, (char *)s, c);
	return (matriz);
}

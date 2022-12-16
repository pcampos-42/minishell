/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:30:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 18:37:20 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*take_operator(char *s, int *i)
{
	char	*token;
	int		s_size;

	if (!s || !i)
		return (0);
	s_size = (int)ft_strlen(s);
	if (ft_is(s[*i], "<>") && *i < s_size - 1)
	{
		if (s[*i] == s[*i + 1])
		{
			token = ft_substr(s, *i, 2);
			*i += 2;
			return (token);
		}
	}
	token = ft_substr(s, *i, 1);
	*i += 1;
	return (token);
}

int	get_quotes_size(char *s, char c)
{
	int	count;

	count = 0;
	while (s[count])
	{
		if (s[count] == c && ((s[count + 1] == '\0')
				|| ft_is(s[count + 1], " \t\r\n\v\f<>|")))
			return (count + 1);
		count++;
	}
	return (1);
}

char	*get_word(char *s, int *i)
{
	int		j;
	char	*token;

	j = *i;
	token = NULL;
	while (s[j])
	{
		if (s[j] && ft_is(s[j], "\""))
			j += get_quotes_size(&s[j + 1], s[j]);
		if (s[j] && ft_is(s[j], "'"))
			j += get_quotes_size(&s[j + 1], s[j]);
		if (!s[j] || ft_is(s[j], " \t\r\n\v\f<>|"))
			break ;
		j++;
	}
	token = ft_substr(s, *i, j - (*i));
	*i = j;
	return (token);
}

char	*get_token(char *s, int reset)
{
	static int	i = 0;
	char		*token;

	if (reset)
		i = 0;
	token = NULL;
	while (s[i])
	{
		if (ft_is(s[i], OPERATORS))
			token = take_operator(s, &i);
		else if (!ft_is(s[i], WHITE_SPACE))
			token = get_word(s, &i);
		if (token)
			return (token);
		i++;
	}
	i = 0;
	return (token);
}

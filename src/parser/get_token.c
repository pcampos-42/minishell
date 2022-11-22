/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:30:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 12:23:01 by pcampos-         ###   ########.fr       */
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
		if (s[count] == c)
			return (count);
		count++;
	}
	return (1);
}

char	*get_word(char *s, int *i)
{
	int		j;
	char	*token;
	char	*seps;

	j = *i;
	token = NULL;
	seps = ft_strjoin(WHITE_SPACE, OPERATORS);
	while (s[j])
	{
		if (ft_is(s[j], "\""))
			j += get_quotes_size(&s[j + 1], s[j]);
		if (ft_is(s[j], "'"))
			j += get_quotes_size(&s[j + 1], s[j]);
		if (ft_is(s[j], seps))
			break ;
		j++;
	}
	token = ft_substr(s, *i, j - (*i));
	*i = j;
	free(seps);
	return (token);
}

	/*	Enquanto existir str
		verificar se e igual a um operador
		se for mandar pra uma funcao que trata disso
		senao verificar se e um white space 
		se for mandar pra uma funcao que trata disso
		verificar se entrou em algum dos 2 de cima e voltou com token
		se sim retornar o token
		senao so continua a andar na str */
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

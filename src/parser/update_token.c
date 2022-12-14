/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:48 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/13 09:32:31 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_quoted_size(char *s)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[0] == s[i])
			return (i + 1);
		i++;
	}
	return (0);
}

static int	get_nquoted_size(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_is(s[i], "\'\""))
			return (i);
		i++;
	}
	return (i);
}

static int	get_seq_size(char *s)
{
	if (ft_is(s[0], "\'\""))
		return (get_quoted_size(s));
	else
		return (get_nquoted_size(s));
}

char	*update_token(char *token, char *new_token, int *index, t_list *env)
{
	char	*str;
	int		size;
	int		i;

	i = *index;
	size = get_seq_size(&token[i]);
	if (size)
	{
		if (ft_is(token[i], "\'\""))
		{
			str = mem_guard(ft_substr(&token[i + 1], 0, size - 2));
			if (token[i] == '"')
				str = expand_str(str, env);
		}
		else
		{
			str = mem_guard(ft_substr(&token[i], 0, size));
			str = expand_str(str, env);
		}
		new_token = token_join(new_token, str);
		*index += size - 1;
	}
	else
		new_token = strjoin_char(new_token, token[i]);
	return (new_token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:48 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 18:53:34 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	size_word(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

static int	check_var_name(char c, int i)
{
	if (i == 0 && (ft_isalpha(c) || c == '_'))
		return (1);
	if (i > 0 && (ft_isalnum(c) || c == '_'))
		return (1);
	return (0);
}

static int	get_size(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!check_var_name(s[i], i))
			return (i);
		i++;
	}
	return (i);
}

char	*expand_var(char *s, char *token, int *i, t_list *env)
{
	t_list	*cursor;
	char	*var_name;
	char	*temp;
	int		size_of_expansion;

	size_of_expansion = get_size(&s[*i + 1]);
	if (!size_of_expansion)
		token = strjoin_char(token, s[*i]);
	else
	{
		var_name = ft_substr(&s[*i + 1], 0, size_of_expansion);
		cursor = exist_env_var(env, var_name);
		if (cursor && cursor->content)
		{
			temp = ft_strchr(cursor->content, '=');
			if (temp)
				token = token_join(token, ft_substr(temp, 1, \
				ft_strlen(temp)), 1);
		}
		free_str(var_name);
		*i += size_of_expansion;
	}
	return (token);
}

char	*expand_str(char *s, t_list *env)
{
	char	*token;
	int		size;
	int		i;

	token = mem_guard(ft_calloc(1, sizeof(char)));
	i = 0;
	while (s[i])
	{
		if (s[i] != '$')
		{
			size = size_word(s);
			token = token_join(token, ft_substr(&s[i], 0, size), 1);
			i += size - 1;
		}
		else if (s[i] == '$' && s[i + 1] && (s[i + 1] == '?'))
		{
			token = token_join(token, ft_itoa(g_exit_status), 1);
			i += 1;
		}
		else if (s[i] == '$')
			token = expand_var(s, token, &i, env);
		i++;
	}
	free_str(s);
	return (token);
}

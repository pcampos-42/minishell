/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_treat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:48 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/19 23:37:33 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	token_need_treat(char *token)
{
	int	i;
	int	s_q;
	int	d_q;
	int	dollar;

	i = 0;
	s_q = 0;
	d_q = 0;
	dollar = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			s_q++;
		if (token[i] == '\"')
			d_q++;
		if (token[i] == '$')
			dollar++;
		i++;
	}
	if (s_q > 1 || d_q > 1 || dollar > 0)
		return (1);
	return (0);
}

char	*treat_token(char *token, t_list *env)
{
	char	*home;
	char	*new_token;
	int		i;

	if (!token)
		return (0);
	home = home_expand(token, env);
	if (home)
	{
		free_str(token);
		return (home);
	}
	if (!token_need_treat(token))
		return (token);
	i = 0;
	new_token = NULL;
	while (token[i])
	{
		new_token = update_token(token, new_token, &i, env);
		i++;
	}
	free_str(token);
	return (new_token);
}

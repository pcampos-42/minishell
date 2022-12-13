/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_treat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:48 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/13 01:18:19 by lucas-ma         ###   ########.fr       */
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
	return (token);
}

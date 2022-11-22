/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:35:43 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 12:19:31 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*do_home_expansion(char *token, t_list *env, int size)
{
	char	*home;
	char	*tmp;

	home = exist_in_env("HOME", env);
	if (!home)
		return (NULL);
	if (size == 1)
		home = ft_substr(home, 5, ft_strlen(home) - 4);
	else
	{
		home = ft_substr(home, 5, ft_strlen(home));
		tmp = ft_substr(token, 1, ft_strlen(token));
		home = ft_strjoin(home, tmp);
	}
	return (home);
}

char	*home_expand(char *token, t_list *env)
{
	char	*new;
	int		size;

	size = ft_strlen(token);
	new = NULL;
	if (!token || !env)
		return (NULL);
	if ((size == 1 && token[0] == '~') \
	|| (size >= 2 && token[0] == '~' && token[1] == '/'))
		new = do_home_expansion(token, env, size);
	return (new);
}

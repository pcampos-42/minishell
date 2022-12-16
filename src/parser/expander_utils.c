/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:48 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 17:34:32 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*strjoin_char(char *str, char c)
{
	char	new[2];
	char	*token;

	new[0] = c;
	new[1] = '\0';
	token = token_join(str, new, 0);
	return (token);
}

t_list	*exist_env_var(t_list *env, char *var_name)
{
	t_list	*cursor;
	int		size;

	if (!var_name || !env)
		return (0);
	cursor = env;
	size = ft_strlen(var_name);
	while (cursor)
	{
		if (!ft_strncmp(var_name, cursor->content, size))
			return (cursor);
		cursor = cursor->next;
	}
	return (NULL);
}

char	*token_join(char *s1, char *s2, int o)
{
	char	*new;

	new = NULL;
	if (s1 && s2)
		new = mem_guard(ft_strjoin(s1, s2));
	free_str(s1);
	if (o)
		free_str(s2);
	return (new);
}

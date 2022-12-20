/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:33:51 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/19 22:36:28 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*mem_guard(void *p)
{
	if (!p)
	{
		ft_putendl_fd("minishell: Out of memory!", 2);
		exit(EXIT_FAILURE);
	}
	return (p);
}

int	ft_is(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	print_matrix(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
	{
		printf("%s\n", mat[i]);
		i++;
	}
	printf("\n");
}

char	*exist_in_env(char	*elem, t_list *env)
{
	t_list	*cursor;

	cursor = env;
	while (cursor)
	{
		if (!ft_strncmp(elem, cursor->content, ft_strlen(elem)))
			return (cursor->content);
		cursor = cursor->next;
	}
	return (NULL);
}

int	get_token_id(char *token)
{
	int	token_size;

	token_size = (int)ft_strlen(token);
	if (token_size == 1)
	{
		if (token[0] == '<')
			return (E_IN);
		else if (token[0] == '>')
			return (E_OUT);
		else if (token[0] == '|')
			return (E_PIPE);
	}
	if (token_size == 2)
	{
		if (token[0] == '<' && token[1] == '<')
			return (E_HDOC);
		else if (token[0] == '>' && token[1] == '>')
			return (E_APPEND);
	}
	return (E_WORD);
}

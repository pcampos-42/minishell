/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmeira <fmeira@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:00:21 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/19 23:33:04 by fmeira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*parser_main(char *s, t_list *env)
{
	t_tree	*tree;
	int		reset;
	int		token_type;
	char	*token;

	reset = 1;
	tree = NULL;
	while (1)
	{
		token = get_token(s, reset);
		if (syntax_error(tree, token))
		{
			g_exit_status = 2;
			free_str(token);
			return (NULL);
		}
		if (!token)
			break ;
		token_type = get_token_id(token);
		if (token_type == E_WORD)
			token = treat_token(token, env);
		build_tree(token, token_type, &tree);
		reset = 0;
	}
	return (tree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:00:21 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 18:50:44 by lucas-ma         ###   ########.fr       */
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
			g_exit_status = WEXITSTATUS(2);
			return (NULL);
		}
		if (!token)
			break ;
		token_type = get_token_id(token);
		if (token_type == E_WORD)
			token = treat_token(token, env);
		build_tree(token, token_type, &tree);
		free_str(token);
		reset = 0;
	}
	return (tree);
}

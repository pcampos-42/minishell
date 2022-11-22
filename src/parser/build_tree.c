/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 22:24:24 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 12:18:21 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_tree	*search_node_to_update(t_tree *tree)
{
	t_tree	*cursor;
	t_tree	*next;

	if (!tree)
		return (NULL);
	if (is_node_pipe(tree))
		cursor = tree->right;
	else
		cursor = tree;
	if (!cursor)
		return (NULL);
	next = cursor->left;
	if (is_node_red(cursor) && !(cursor->token))
		return (cursor);
	else if (next && is_node_red(next) && !(next->token))
		return (next);
	else if (is_node_cmd(cursor))
		return (cursor);
	return (NULL);
}

static int	check_built_in(char *token)
{
	if (!ft_strncmp(token, "echo", 5))
		return (E_BUILT);
	if (!ft_strncmp(token, "cd", 3))
		return (E_BUILT);
	if (!ft_strncmp(token, "pwd", 4))
		return (E_BUILT);
	if (!ft_strncmp(token, "export", 7))
		return (E_BUILT);
	if (!ft_strncmp(token, "unset", 6))
		return (E_BUILT);
	if (!ft_strncmp(token, "env", 4))
		return (E_BUILT);
	if (!ft_strncmp(token, "exit", 5))
		return (E_BUILT);
	return (E_CMD);
}

void	build_tree(char *token, int token_id, t_tree **tree)
{
	t_tree	*node;

	if (token_id == E_WORD)
	{
		node = search_node_to_update(*tree);
		if (node)
			update_node(node, token);
		else
		{
			token_id = check_built_in(token);
			add_new_node(tree, update_node(create_node(token_id), token));
		}
	}
	else
		add_new_node(tree, create_node(token_id));
}

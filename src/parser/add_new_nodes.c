/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:51:32 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 18:16:36 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_new_red(t_tree **tree, t_tree *node)
{
	t_tree	*first;
	t_tree	*next;	

	if (!tree)
		return ;
	first = *tree;
	if (!first)
		add_node_on_top(tree, node);
	else if (is_node_cmd(first) || is_node_red(first))
		add_node_on_left(first, node);
	else if (is_node_pipe(first))
	{
		next = first->right;
		if (!next || is_node_red(next))
			add_node_on_right(first, node);
		else
			add_node_on_left(next, node);
	}
}

static void	add_new_cmd(t_tree **tree, t_tree *node)
{
	t_tree	*first;

	first = *tree;
	if (!first || is_node_red(first))
		add_node_on_top(tree, node);
	else if (is_node_pipe(first))
		add_node_on_right(first, node);
}

static void	add_new_pipe(t_tree **tree, t_tree *node)
{
	add_node_on_top(tree, node);
}

void	add_new_node(t_tree **tree, t_tree *node)
{
	if (is_node_red(node))
		add_new_red(tree, node);
	else if (is_node_cmd(node))
		add_new_cmd(tree, node);
	else if (is_node_pipe(node))
		add_new_pipe(tree, node);
}

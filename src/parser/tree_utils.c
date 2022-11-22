/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:19:55 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 12:20:22 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tree	*create_node(int id)
{
	t_tree	*node;

	node = mem_guard(malloc(sizeof(t_tree)));
	if (!node)
		return (0);
	node->type = id;
	node->token = NULL;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	add_node_on_left(t_tree *current, t_tree *new_node)
{
	if (!current || !new_node)
		return ;
	if (current->left)
	{
		new_node->left = current->left;
		current->left->parent = new_node;
	}
	current->left = new_node;
	new_node->parent = current;
}

void	add_node_on_right(t_tree *node, t_tree *new_node)
{
	if (!node || !new_node)
		return ;
	if ((node->right))
	{
		new_node->left = node->right;
		node->right->parent = new_node;
	}
	node->right = new_node;
	new_node->parent = node;
}

void	add_node_on_top(t_tree **tree, t_tree *node)
{
	t_tree	*first;

	first = *tree;
	if (!first)
		first = node;
	else
	{
		node->left = first;
		first->parent = node;
		first = node;
	}
	*tree = first;
}

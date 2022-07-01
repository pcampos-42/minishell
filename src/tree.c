/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:38:17 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/05/31 14:37:24 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_add_root(t_tree **root, t_tree *new_root)
{
	if (!root || !(*root) || !new_root)
		return ;
	new_root->right = *root;
	(*root)->parent = new_root;
	(*root) = new_root;
}

void	tree_add_right(t_tree **root, t_tree *new)
{
	if (!root || !(*root) || !new)
		return ;
	if ((*root)->right)
	{
		new->right = (*root)->right;
		(*root)->right->parent = new;
	}
	(*root)->right = new;
	new->parent = (*root);
}

void	tree_add_left(t_tree **root, t_tree *new)
{
	if (!root || !(*root) || !new)
		return ;
	if ((*root)->left)
	{
		new->left = (*root)->left;
		(*root)->left->parent = new;
	}
	(*root)->left = new;
	new->parent = (*root);
}

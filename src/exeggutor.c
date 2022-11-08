/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:59:14 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/08 19:22:08 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exeggutor(t_tree **root, t_list *env)
{
	t_tree	*tree;

	tree = *root;
	while (tree->right->token == PIPE)
	{
		if (!do_comand(tree->left, env))
			return ;
		tree = tree->right;
	}
	if (!tree->right)
		if (!do_comand(tree->left, env))
			return ;
	else
	{
		tree = tree->right;
		if (!do_comand(tree->left, env))
			return ;
	}
}

int	do_comand(t_tree *tree, t_list *env)
{

}

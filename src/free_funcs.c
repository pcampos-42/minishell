/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:20:53 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/23 14:47:12 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free_str(matrix[i]);
	free (matrix);
}

void	free_str(char *str)
{
	if (str)
		free(str);
}

static void	free_node(t_tree *node)
{
	if (is_node_red(node))
	{
		if (node->token)
			free_str(node->token);
	}
	else if (is_node_cmd(node))
	{
		if (node->token)
			free_matrix(node->token);
	}
	free(node);
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free_node(tree);
}

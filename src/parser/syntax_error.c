/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:48 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/13 12:59:41 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error(char *token)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

int	error_analysis(t_tree *tree, char *token)
{
	t_tree	*node;

	if (!token && is_node_pipe(tree) && !tree->right)
	{
		print_error(token);
		return (1);
	}
	if (is_node_pipe(tree))
		node = tree->right;
	else
		node = tree;
	if (branch_analysis(node))
	{
		print_error(token);
		return (1);
	}
	return (0);
}

int	branch_analysis(t_tree *node)
{
	while (node)
	{
		if (!(node->token))
			return (1);
		node = node->left;
	}
	return (0);
}

static int	is_syntax_error(t_tree *tree, char *token)
{
	int	status;

	status = 0;
	if (!token || get_token_id(token) != E_WORD)
		status = error_analysis(tree, token);
	return (status);
}

int	syntax_error(t_tree *tree, char *token)
{
	if (is_syntax_error(tree, token))
	{
		free_tree(tree);
		free_str(token);
		return (2);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:26:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 12:20:36 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	update_node_red(t_tree *node, char *token)
{
	node->token = ft_strdup(token);
}

static int	matrix_size(char **mat)
{
	int	i;

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

static char	**update_matrix(char **matrix, char *token)
{
	int		size;
	int		i;
	char	**new;

	if (!matrix)
	{
		new = mem_guard(malloc(2 * sizeof(char *)));
		new[0] = mem_guard(ft_strdup(token));
		new[1] = NULL;
	}
	else
	{
		size = matrix_size(matrix);
		new = mem_guard(malloc((size + 2) * sizeof(char *)));
		i = -1;
		while (matrix[++i])
			new[i] = matrix[i];
		new[i] = ft_strdup(token);
		new[i + 1] = NULL;
		free(matrix);
	}
	return (new);
}

static void	update_node_cmd(t_tree *node, char *token)
{
	char	**temp;

	temp = node->token;
	node->token = update_matrix(temp, token);
}

t_tree	*update_node(t_tree *node, char *token)
{
	if (!node || !token)
		return (NULL);
	if (is_node_red(node))
		update_node_red(node, token);
	else if (is_node_cmd(node))
		update_node_cmd(node, token);
	return (node);
}

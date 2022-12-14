/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:53:20 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/12 16:49:53 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_node_red(t_tree *node)
{
	if (!node)
		return (0);
	if (node->type >= E_IN && node->type <= E_HDOC)
		return (1);
	return (0);
}

int	is_node_pipe(t_tree *node)
{
	if (!node)
		return (0);
	if (node->type == E_PIPE)
		return (1);
	return (0);
}

int	is_node_cmd(t_tree *node)
{
	if (!node)
		return (0);
	if (node->type == E_CMD || node->type == E_BUILT)
		return (1);
	return (0);
}

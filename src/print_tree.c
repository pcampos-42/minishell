/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:06:22 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 16:32:00 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser/parser.h"

#define COUNT 10

/*
 Code based in https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
*/

static void	print2dutil(t_tree *root, int space);

/*
 Code based in https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
*/

void	print2d(t_tree *root)
{
	print2dutil(root, 0);
}

void	print_data(t_tree node)
{
	if (node.type == E_CMD || node.type == E_BUILT)
		print_matrix(node.token);
	else
		printf("%s\n", (char *)node.token);
}

void	print_node(t_tree *node)
{
	if (node->type == E_PIPE)
		printf("|\n");
	else
	{
		if (node->type == E_OUT)
			printf("> ");
		else if (node->type == E_APPEND)
			printf(">> ");
		else if (node->type == E_IN)
			printf("< ");
		else if (node->type == E_HDOC)
			printf("<< ");
		print_data(*node);
	}
}

// It does reverse inorder traversal
static void	print2dutil(t_tree *root, int space)
{
	if (root == NULL)
		return ;
	// Increase distance between levels
	space += COUNT;
	// Process right child first
	print2dutil(root->right, space);
	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	//printf("%s\n", root->data);
	print_node(root);
	// Process left child
	print2dutil(root->left, space);
}

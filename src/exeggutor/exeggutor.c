/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:59:14 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/22 14:39:57 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exeggutor(t_tree **root, t_list *env)
{
	t_tree	*tree;

	tree = *root;
	while (tree->right->type == E_PIPE)
	{
		if (tree->left->type == E_CMD)
			do_comand(tree->left, env);
		else
			builtins(tree->left, env);
		tree = tree->right;
	}
	if (!tree->right)
	{
		if (tree->type == E_CMD)
			do_comand(tree, env);
		else
			builtins(tree, env);
	}
	else
	{
		finish_tree(tree, env);
	}
}

void	finish_tree(t_tree *tree, t_list *env)
{
	if (tree->left->type == E_CMD)
		do_comand(tree->left, env);
	else
		builtins(tree->left, env);
	if (tree->right->type == E_CMD)
		do_comand(tree->right, env);
	else
		builtins(tree->right, env);
}

void	do_comand(t_tree *tree, t_list *env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!pipe(pipe_fd))
	{	
		ft_putendl_fd("pipe error", 2);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("fork error", 2);
		return ;
	}
	if (!pid)
	{
		child_labor(tree, env, pipe_fd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	child_labor(t_tree *tree, t_list *env, int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	execve(get_path(tree, env), tree->token, env_matrix(env));
}
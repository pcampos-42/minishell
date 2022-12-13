/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:59:14 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/12 21:50:25 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_built(t_tree *tree)
{
	(void)tree;
	return (1);
}

void	exeggutor(t_tree **root, t_list **env, int c)
{
	t_tree		*tree;
	t_exec		exec;

	exec.fd = 0;
	exec.n_c = c;
	exec.c = c;
	tree = *root;
	if (!tree->parent && tree->type == E_BUILT)
		builtins(tree, env, redir_built(tree));
	else
	{
		start_tree(tree, *env, &exec);
		while (tree->parent)
		{
			tree = tree->parent;
			do_comand(tree->right, *env, &exec);
			exec.c--;
		}
	}
	waitpid(exec.pid, &g_exit_status, 0);
	while (exec.n_c--)
		wait(NULL);
}

void	start_tree(t_tree *tree, t_list *env, t_exec *exec)
{
	if (tree->type == E_PIPE)
	{
		do_comand(tree->left, env, exec);
		exec->c--;
		do_comand(tree->right, env, exec);
		exec->c--;
	}
	else
		do_comand(tree, env, exec);
}

void	do_comand(t_tree *tree, t_list *env, t_exec *exec)
{
	if (pipe(tree->p) == -1)
		ft_putendl_fd("Error: Pipe failed", 2);
	exec->pid = fork();
	if (exec->pid < 0)
		ft_putendl_fd("Error: Fork failed", 2);
	if (exec->pid == 0)
		child_labor(tree, env, exec);
	if (tree->parent)
	{
		if (exec->fd > 0)
			close(exec->fd);
		close(tree->p[1]);
		exec->fd = tree->p[0];
	}
}

void	child_labor(t_tree *tree, t_list *env, t_exec *exec)
{
	close(tree->p[0]);
	redir(tree, exec);
	rl_clear_history();
	if (tree->type == E_BUILT)
	{
		builtins(tree, &env, 1);
		exit(g_exit_status);
	}
	execve(cmd_path(((char **)tree->token)[0], env),
		tree->token, env_matrix(env));
	exit(127);
}

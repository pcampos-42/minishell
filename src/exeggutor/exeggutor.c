/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:59:14 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/20 00:43:32 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exeggutor(t_tree **root, t_list **env, int c)
{
	t_tree		*tree;
	t_exec		exec;

	exec.env = *env;
	exec.fd = 0;
	exec.n_c = c;
	exec.c = c;
	tree = *root;
	call_sigact(SI_DFL, env);
	if (!tree->parent && tree->type == E_HDOC)
		return (fake_heredoc(tree));
	if (!tree->parent && tree->type == E_BUILT)
		return (builtins(tree, &exec, redir_built(tree, &exec)));
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
	wait_cmds(exec.pid, c, *env);
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
	if (exec->c != 1)
	{
		if (exec->fd > 0)
			close(exec->fd);
		close(tree->p[1]);
		exec->fd = tree->p[0];
	}
}

void	child_labor(t_tree *tree, t_list *env, t_exec *exec)
{
	char	**m_env;

	if (tree->type == E_HDOC)
		return (fake_heredoc(tree));
	m_env = env_matrix(env);
	close(tree->p[0]);
	redir(tree, exec);
	rl_clear_history();
	if (tree->type == E_BUILT)
	{
		builtins(tree, exec, 1);
		free(m_env);
		exit(g_exit_status);
	}
	execve(cmd_path(((char **)tree->token)[0], env, m_env),
		tree->token, m_env);
	free_matrix(m_env);
	if (exec->doc == 1)
		unlink(".heredoc_tmp");
	exit(127);
}

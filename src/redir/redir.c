/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:49 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/23 13:59:52 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	n_redirs(t_tree *branch, t_exec *exec)
{
	exec->in = 0;
	exec->out = 0;
	while (branch->left)
	{
		branch = branch->left;
		if (branch->type == E_IN || branch->type == E_HDOC)
			exec->in++;
		if (branch->type == E_OUT || branch->type == E_APPEND)
			exec->out++;
	}
}

void	redir_in(t_tree *branch, t_exec *exec)
{
	int	i;

	i = exec->in + 1;
	while (branch->left)
	{
		branch = branch->left;
		if (branch->type == E_IN || branch->type == E_HDOC)
		{
			i--;
			if (branch->type == E_IN)
				no_doc(branch, exec, i);
			else
				handle_heredoc(branch, exec, i);
		}
	}
}

void	redir_out(t_tree *branch, t_exec *exec)
{
	int	i;
	int	fd;

	i = exec->out + 1;
	while (branch->left)
	{
		branch = branch->left;
		if (branch->type == E_OUT || branch->type == E_APPEND)
		{
			if (branch->type == E_OUT)
				fd = open(branch->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(branch->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
			i--;
			if (fd == -1)
				redir_error(branch);
			if (i == exec->out)
				dup2(fd, STDOUT_FILENO);
			else
				close(fd);
		}
	}
}

void	redir(t_tree *branch, t_exec *exec)
{
	call_sigact(SI_HDOC, &(exec->env));
	n_redirs(branch, exec);
	if (exec->in)
	{
		if (exec->fd)
			close (exec->fd);
		redir_in(branch, exec);
	}
	else
		dup2(exec->fd, STDIN_FILENO);
	redir_2(branch, exec);
}

void	redir_2(t_tree *branch, t_exec *exec)
{
	if (exec->out)
	{
		close(branch->p[1]);
		redir_out(branch, exec);
	}
	else
	{
		if (exec->c > 1)
		{
			dup2(branch->p[1], STDOUT_FILENO);
			close(branch->p[1]);
		}
		else
			close(branch->p[1]);
	}
}

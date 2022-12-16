/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:49 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/16 19:29:52 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	redir(t_tree *branch, t_exec *exec)
// {
// 	if (exec->fd != 0)
// 		dup2(exec->fd, STDIN_FILENO);
// 	if (exec->c > 1)
// 		dup2(branch->p[1], STDOUT_FILENO);
// 	close (branch->p[1]);
// }

void	redir_error(t_tree *branch)
{
	ft_putstr_fd("Error: couldn't open file: ", 2);
	ft_putstr_fd(branch->token, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

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
	exec->doc = 0;
	while (branch->left)
	{
		if (branch->type == E_IN || branch->type == E_HDOC)
		{
			branch = branch->left;
			i--;
			if (branch->type == E_IN)
				no_doc(branch, exec, i);
			else
			{
				if (i == exec->in)
					dup2(branch->p[0], STDIN_FILENO);
				exec->doc = 1;
			}
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
	n_redirs(branch, exec);
	if (exec->in)
	{
		if (exec->fd)
			close (exec->fd);
		redir_in(branch, exec);
	}
	else
		dup2(exec->fd, STDIN_FILENO);
	if (exec->out)
	{
		close(branch->p[1]);
		redir_out(branch, exec);
	}
	else
	{
		if (exec->c > 1)
			dup2(branch->p[1], STDOUT_FILENO);
		else
			close(branch->p[1]);
	}
}

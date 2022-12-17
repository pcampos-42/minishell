/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:12:47 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/17 05:43:52 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_built_in(t_tree *branch)
{
	while (branch->left)
	{
		branch = branch->left;
		if (branch->type == E_IN || branch->type == E_HDOC)
		{
			if (branch->type == E_IN)
			{
				if (open(branch->token, O_RDONLY, 0644) == -1)
					redir_error(branch);
			}
			else
				fake_heredoc(branch);
		}
	}
}

int	redir_built_out(t_tree *branch, t_exec *exec)
{
	int	i;
	int	fd;
	int	tmp;

	i = exec->out + 1;
	while (branch->left)
	{
		branch = branch->left;
		if (branch->type == E_OUT || branch->type == E_APPEND)
		{
			if (branch->type == E_OUT)
				tmp = open(branch->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				tmp = open(branch->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
			i--;
			if (tmp == -1)
				redir_error(branch);
			if (i == exec->out)
				fd = tmp;
			else
				close(tmp);
		}
	}
	return (fd);
}

int	redir_built(t_tree *branch, t_exec *exec)
{
	n_redirs(branch, exec);
	if (exec->in > 0)
		redir_built_in(branch);
	if (exec->out > 0)
		return (redir_built_out(branch, exec));
	else
		return (1);
}

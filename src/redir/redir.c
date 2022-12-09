/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:49 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/09 22:28:01 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir(t_tree *branch, t_exec *exec)
{
	if (exec->fd != 0)
		dup2(exec->fd, STDIN_FILENO);
	if (exec->c > 1)
		dup2(branch->p[1], STDOUT_FILENO);
	close (exec->fd);
	close (branch->p[1]);
}

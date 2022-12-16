/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:51:10 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/16 19:51:57 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_doc(t_tree *branch, t_exec *exec, int i)
{
	int	fd;

	fd = open(branch->token, O_RDONLY, 0644);
	if (fd == -1)
		redir_error(branch);
	if (i == exec->in)
		dup2(fd, STDIN_FILENO);
	else
		close(fd);
}

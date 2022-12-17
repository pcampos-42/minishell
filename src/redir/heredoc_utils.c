/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:51:10 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/16 21:30:36 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fake_heredoc(t_tree *branch)
{
	char	*buf;
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strdup(branch->token);
	tmp = ft_strjoin(tmp2, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		buf = get_next_line(0);
		if (buf)
		{
			if (ft_strlen(buf) == ft_strlen(tmp)
				&& !ft_strncmp(tmp, buf, ft_strlen(branch->token)))
				break ;
			free (buf);
		}
		else
			break ;
	}
	free (tmp);
	free (tmp2);
	free (buf);
}

void	fill_heredoc(t_tree *branch, int fd)
{
	char	*buf;
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strdup(branch->token);
	tmp = ft_strjoin(tmp2, "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		buf = get_next_line(0);
		if (buf)
		{
			if (ft_strlen(buf) == ft_strlen(tmp)
				&& !ft_strncmp(tmp, buf, ft_strlen(branch->token)))
				break ;
			write(fd, buf, ft_strlen(buf));
			free (buf);
		}
		else
			break ;
	}
	free (tmp);
	free (tmp2);
	free (buf);
}

void	handle_heredoc(t_tree *branch, t_exec *exec, int i)
{
	int	fd;

	if (i != exec->in)
	{
		fake_heredoc(branch);
		return ;
	}
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(branch);
	fill_heredoc(branch, fd);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY, 0644);
	if (fd == -1)
		redir_error(branch);
	dup2(fd, STDIN_FILENO);
	exec->doc = 1;
}

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

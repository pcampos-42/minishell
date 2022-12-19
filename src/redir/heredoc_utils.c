/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 23:51:10 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/17 07:33:15 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parser/parser.h"

void	fake_heredoc(t_tree *branch)
{
	char	*buf;
	char	*tmp;

	tmp = ft_strdup(branch->token);
	while (1)
	{
		buf = readline("> ");
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
	free (buf);
}

void	fill_2(int fd, t_list *env, char *buf)
{
	char	*parser;
	char	*tmp;

	tmp = ft_strjoin(buf, "\n");
	parser = treat_token(tmp, env);
	write(fd, parser, ft_strlen(parser));
	free (buf);
	free (tmp);
}

void	fill_heredoc(t_tree *branch, int fd, t_list *env)
{
	char	*buf;
	char	*tmp;

	tmp = ft_strdup(branch->token);
	while (1)
	{
		buf = readline("> ");
		if (buf)
		{
			if (ft_strlen(buf) == ft_strlen(tmp)
				&& !ft_strncmp(tmp, buf, ft_strlen(branch->token)))
				break ;
			fill_2(fd, env, buf);
		}
		else
			break ;
	}
	free (tmp);
	free (buf);
}

void	handle_heredoc(t_tree *branch, t_exec *exec, int i)
{
	int	fd;

	call_sigact(SI_HDOC, &(exec->env));
	if (i != exec->in)
	{
		fake_heredoc(branch);
		return ;
	}
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		redir_error(branch);
	fill_heredoc(branch, fd, exec->env);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY, 0644);
	if (fd == -1)
		redir_error(branch);
	dup2(fd, STDIN_FILENO);
	unlink(".heredoc_tmp");
}

void	no_doc(t_tree *branch, t_exec *exec, int i)
{
	int	fd;

	fd = open(((char *)branch->token), O_RDONLY, 0644);
	if (fd == -1)
		redir_error(branch);
	if (i != exec->in)
		close(fd);
	else
		dup2(fd, STDIN_FILENO);
}

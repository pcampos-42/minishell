/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:56:24 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/19 16:21:40 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*absolute_path(char *cmd, char **m_env)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(" is a directory", 2);
		free(m_env);
		g_exit_status = 126;
		exit(g_exit_status);
	}
	if (access(cmd, X_OK) < 0)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Command not found", 2);
		free(m_env);
		g_exit_status = 127;
		exit(g_exit_status);
	}
	return (cmd);
}

char	*cmd_path(char *cmd, t_list *env, char **m_env)
{
	if (cmd[0] == '/')
		return (absolute_path(cmd, m_env));
	else
		return (relative_path(cmd, env));
}

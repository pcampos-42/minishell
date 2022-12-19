/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:14:24 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/19 16:04:58 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path(char *str, char *path)
{
	struct stat	buf;

	lstat(path, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" is a directory", 2);
		g_exit_status = 126;
		exit(g_exit_status);
	}
	if (access(path, X_OK) >= 0)
		return (1);
	return (0);
}

char	*get_cmd_path(char **path, char *cmd)
{
	char	*tmp;
	int		i;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (is_path(cmd, tmp))
		{
			free_matrix(path);
			free(cmd);
			return (tmp);
		}
		free(tmp);
	}
	free_matrix(path);
	free(cmd);
	return (NULL);
}

char	*get_path(char *env, char *cmd)
{
	char	**tmp;
	char	*tmp2;

	if (ft_strncmp(env, "PATH=", 5))
		return (NULL);
	tmp = ft_split(env, ':');
	tmp2 = ft_strjoin("/", cmd);
	return (get_cmd_path(tmp, tmp2));
}

void	rlp_error_msg(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Command not found", 2);
}

char	*relative_path(char *cmd, t_list *env)
{
	char	*path;
	char	*tmp;
	t_list	*tenv;

	tenv = env;
	if (cmd[0] && cmd[0] == '.')
	{
		path = getcwd(NULL, 0);
		tmp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (is_path(cmd, path))
			return (path);
	}
	while (tenv)
	{
		path = get_path(tenv->content, cmd);
		if (is_path(cmd, path))
			return (path);
		free(path);
		tenv = tenv->next;
	}
	rlp_error_msg(cmd);
	return (NULL);
}

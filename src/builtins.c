/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:38:09 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/08 12:42:20 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_func(t_tree branch)
{
	int	fd;

	fd = 1;
	//if (branch.right->token)
	//	fd = open(branch.right->token, O_WRONLY, O_APPEND);
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(((char **)(branch.token))[0], 2);
		return ;
	}
	if (ft_strncmp(((char **)(branch.token))[1], "-n", 2))
		ft_putstr_fd(((char **)(branch.token))[1], fd);
	else
		ft_putendl_fd(((char **)(branch.token))[2], fd);
	if (fd > 2)
		close(fd);
}

void	pwd_func(t_tree branch)
{
	char	*tmp;
	int		fd;

	fd = 1;
	//if (branch.right)
	//	fd = open(branch.right->token, O_WRONLY, O_TRUNC);
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(((char **)(branch.token))[0], 2);
		return ;
	}
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	ft_putendl_fd(tmp, fd);
	free (tmp);
	if (fd > 2)
		close(fd);
}

void	env_func(t_tree branch, t_list *env)
{
	int		fd;

	fd = 1;
	//if (branch.right)
	//	fd = open(branch.right->token, O_WRONLY, O_APPEND);
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(((char **)(branch.token))[0], 2);
		return ;
	}
	print_env(env, fd);
	if (fd > 2)
		close(fd);
}

void	builtins(t_tree branch, t_list *env)
{
	if (!ft_strncmp(((char **)(branch.token))[0], "echo", 4))
		echo_func(branch);
	else if (!ft_strncmp(((char **)(branch.token))[0], "pwd", 3))
		pwd_func(branch);
	else if (!ft_strncmp(((char **)(branch.token))[0], "env", 3))
		env_func(branch, env);
	else if (!ft_strncmp(((char **)(branch.token))[0], "cd", 2))
		cd_func(branch, &env);
	else if (!ft_strncmp(((char **)(branch.token))[0], "export", 6))
		export_func(branch, &env);
	else if (!ft_strncmp(((char **)(branch.token))[0], "unset", 5))
	 	unset_func(branch, &env);
}

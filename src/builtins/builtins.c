/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:38:09 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/12 21:13:57 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_args(char **token, int fd, int i)
{
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putstr_fd(token[i], fd);
}

void	print_args_nl(char **token, int fd, int i)
{
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putendl_fd(token[i], fd);
}

void	builtins(t_tree *branch, t_list **env, int fd)
{
	if (!ft_strncmp(((char **)(branch->token))[0], "echo", 5))
		echo_func(branch, fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "pwd", 4))
		pwd_func(fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "env", 4))
		print_env(*env, fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "cd", 3))
		cd_func(branch, env);
	else if (!ft_strncmp(((char **)(branch->token))[0], "export", 7))
		export_func(branch, env, fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "unset", 6))
		unset_func(branch, env);
	else if (!ft_strncmp(((char **)(branch->token))[0], "exit", 5))
		exit_func(branch);
}

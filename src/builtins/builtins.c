/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:38:09 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/19 19:52:37 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_args(char **token, int fd, int i)
{
	if (!token[i])
		return ;
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putstr_fd(token[i], fd);
}

void	print_args_nl(char **token, int fd, int i)
{
	if (!token[i])
		return (ft_putchar_fd('\n', fd));
	while (token[i + 1])
	{
		ft_putstr_fd(token[i++], fd);
		ft_putchar_fd(' ', fd);
	}
	ft_putendl_fd(token[i], fd);
}

void	builtins(t_tree *branch, t_exec *exec, int fd)
{
	if (!ft_strncmp(((char **)(branch->token))[0], "echo", 5))
		echo_func(branch, fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "pwd", 4))
		pwd_func(fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "env", 4))
		print_env(exec->env, fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "cd", 3))
		cd_func(branch, &(exec->env));
	else if (!ft_strncmp(((char **)(branch->token))[0], "export", 7))
		export_func(branch, &(exec->env), fd);
	else if (!ft_strncmp(((char **)(branch->token))[0], "unset", 6))
		unset_func(branch, &(exec->env));
	else if (!ft_strncmp(((char **)(branch->token))[0], "exit", 5))
		exit_func(branch, exec->env);
}

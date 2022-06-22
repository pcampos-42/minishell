/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:38:09 by pcampos-          #+#    #+#             */
/*   Updated: 2022/06/22 11:42:20 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Cada funcao tem comentario com o seu status
//mas no geral falta tratar dos erros

//testado sem erros detetados
void	echo_func(t_tree branch)
{
	int	fd;

	if (branch.right)
		fd = open(branch.right->token[0], O_WRONLY, O_APPEND);
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(branch.token[0], 2);
		return ;
	}
	if (!ft_strncmp(branch.token[1], "-n", 2))
		ft_putstr_fd(branch.token[2], fd);
	else
		ft_putendl_fd(branch.token[2], fd);
	if (fd > 2)
		close(fd);
}

//testado sem erros detetados
void	pwd_func(t_tree branch)
{
	char	*tmp;
	int		fd;

	if (branch.right)
		fd = open(branch.right->token[0], O_WRONLY, O_TRUNC);
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(branch.token[0], 2);
		return ;
	}
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	ft_putendl_fd(tmp, fd);
	free (tmp);
	if (fd > 2)
		close(fd);
}

//testado sem erros detetados
void	env_func(t_tree branch, t_list *env)
{
	int		fd;

	if (branch.right)
		fd = open(branch.right->token[0], O_WRONLY, O_APPEND);
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(branch.token[0], 2);
		return ;
	}
	print_env(env, fd);
	if (fd > 2)
		close(fd);
}

//testado sem erros detetados
//deve ser testado melhor os leaks
void	cd_func(t_tree branch, t_list **env)
{
	t_list	*tmp;
	char	*pwd;

	tmp = *env;
	pwd = getcwd(NULL, 0);
	while (ft_strncmp((*env)->content, "OLDPWD", 6) != 0 && (*env)->next)
		(*env) = (*env)->next;
	if (ft_strncmp((*env)->content, "OLDPWD", 6) != 0)
		(*env) = (*env)->next;
	(*env)->content = ft_strjoin("OLDPWD=/", pwd);
	chdir(branch.token[1 + 1]);
	free (pwd);
	pwd = getcwd(NULL, 0);
	(*env) = tmp;
	while (ft_strncmp((*env)->content, "PWD", 3) != 0 && (*env)->next)
		(*env) = (*env)->next;
	if (ft_strncmp((*env)->content, "PWD", 3) != 0)
		(*env) = (*env)->next;
	(*env)->content = ft_strjoin("PWD=/", pwd);
	free (pwd);
	pwd_func(branch);
}

void	builtins(t_tree branch, t_list *env)
{
	if (!ft_strncmp(branch.token[0], "echo", 4))
		echo_func(branch);
	if (!ft_strncmp(branch.token[0], "pwd", 3))
		pwd_func(branch);
	if (!ft_strncmp(branch.token[0], "env", 3))
		env_func(branch, env);
	if (!ft_strncmp(branch.token[0], "cd", 2))
		cd_func(branch, &env);
	// if (!ft_strncmp(branch->token[0], "exit", 4))
	// 	exit_func(branch, env);
	// if (!ft_strncmp(branch->token[0], "export", 6))
	// 	export_func();
	// if (!ft_strncmp(branch->token[0], "unset", 5))
	// 	unset_func();
}

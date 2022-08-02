/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:38:09 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/02 11:17:05 by pcampos-         ###   ########.fr       */
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
		fd = open(branch.right->token, O_WRONLY, O_APPEND);
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(((char **)(branch.token))[0], 2);
		return ;
	}
	if (ft_strncmp(((char **)(branch.token))[1], "-n", 2))
		ft_putstr_fd(((char **)(branch.token))[2], fd);
	else
		ft_putendl_fd(((char **)(branch.token))[2], fd);
	if (fd > 2)
		close(fd);
}

//testado sem erros detetados
void	pwd_func(t_tree branch)
{
	char	*tmp;
	int		fd;

	if (branch.right)
		fd = open(branch.right->token, O_WRONLY, O_TRUNC);
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(((char **)(branch.token))[1], 2);
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
		fd = open(branch.right->token, O_WRONLY, O_APPEND);
	else
		fd = 1;
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

//falta testar
void	unset_func(t_tree branch, t_list **env)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *env;
	while (ft_strncmp(tmp->next->content, branch.left->token,
			ft_strlen(tmp->next->content)) && tmp->next != NULL)
		tmp = tmp->next;
	tmp2 = tmp;
	if (tmp->next != NULL)
		tmp = tmp->next;
	tmp2->next = tmp->next;
	ft_lstdelone(tmp, free);
}

void	builtins(t_tree branch, t_list *env)
{
	if (!ft_strncmp(((char **)(branch.token))[0], "echo", 4))
		echo_func(branch);
	else
	if (!ft_strncmp(((char **)(branch.token))[0], "pwd", 3))
		pwd_func(branch);
	else
	if (!ft_strncmp(((char **)(branch.token))[0], "env", 3))
		env_func(branch, env);
	else
	if (!ft_strncmp(((char **)(branch.token))[1], "cd", 2))
		cd_func(branch, &env);
	else
	// if (!ft_strncmp(b((char **)(branch.token))[0], "exit", 4))
	// 	exit_func(branch, env);
	//else
	if (!ft_strncmp(((char **)(branch.token))[0], "export", 6))
		export_func(branch, &env);
	else
	if (!ft_strncmp(((char **)(branch.token))[0], "unset", 5))
	 	unset_func(branch, &env);
}

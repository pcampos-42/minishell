/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:58:02 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/19 20:09:07 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_valid_path(t_tree *branch)
{
	if (access(((char **)(branch->token))[1], F_OK) < 0)
	{
		ft_putstr_fd("Can´t access ", 2);
		ft_putendl_fd(((char **)(branch->token))[1], 2);
		return (1);
	}
	else
		return (0);
}

int	search_wd(t_list *env, char *str, int i)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->content, str, i))
			return (1);
		else
			tmp = tmp->next;
	}
	return (0);
}

void	cd_func(t_tree *branch, t_list **env)
{
	if (check_valid_path(branch))
	{
		printf("Path Invalido\n");
		return ;
	}
	do_cd(branch, env);
}

void	update_pwd(t_list **env, char *pwd, t_list *tmp)
{
	pwd = getcwd(NULL, 0);
	tmp = *env;
	if (!search_wd(tmp, "PWD=", 4))
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("PWD=/", pwd)));
	else
	{
		while (ft_strncmp(tmp->content, "PWD=", 4) != 0 && tmp->next)
			tmp = tmp->next;
		free_str((char *)tmp->content);
	}
	tmp->content = ft_strjoin("PWD=/", pwd);
	free (pwd);
}

void	do_cd(t_tree *branch, t_list **env)
{
	char	*pwd;
	t_list	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = *env;
	if (!search_wd(tmp, "OLDPWD=", 7))
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("OLDPWD=/", pwd)));
	else
	{
		while (tmp->next && ft_strncmp(tmp->content, "OLDPWD=/", 8) != 0)
			tmp = tmp->next;
		free (tmp->content);
	}
	tmp->content = ft_strjoin("OLDPWD=", pwd);
	free (pwd);
	if (chdir(((char **)(branch->token))[1]) == -1)
		return ;
	update_pwd(env, pwd, tmp);
	g_exit_status = 0;
}

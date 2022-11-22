/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:38:52 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/22 14:35:34 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_list **env, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		ft_lstadd_back(env, ft_lstnew(envp[i]));
}

void	print_env(t_list *env, int fd)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strchr(tmp->content, '='))
			ft_putendl_fd(tmp->content, fd);
		tmp = tmp->next;
	}
}

char	**env_matrix(t_list *env)
{
	int		size;
	int		i;
	char	**matrix;
	t_list	*tmp;

	i = 0;
	tmp = env;
	size = ft_lstsize(env);
	matrix = malloc(sizeof(char *) * size + 1);
	while (tmp->next != NULL)
	{
		matrix[i++] = tmp->content;
		tmp = tmp->next;
	}
	matrix[i] = tmp->content;
	return (matrix);
}

void	env_func(t_tree *branch, t_list *env)
{
	int	fd;

	if (branch->left)
	{
		if (branch->left)
		{
			return ;
		}
	}
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(((char **)(branch->token))[0], 2);
		return ;
	}
	print_env(env, fd);
	if (fd > 2)
		close(fd);
}

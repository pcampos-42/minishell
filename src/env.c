/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:38:52 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/15 17:19:16 by pcampos-         ###   ########.fr       */
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

//void	declare_x(t_list *env, int fd)
//{
//}

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

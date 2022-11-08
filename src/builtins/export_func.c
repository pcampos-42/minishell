/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:15:49 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/08 19:34:59 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exist_var(t_list *env, char *name)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, name, ft_strlen(name) - 1))
			return (1);
		else
			tmp = tmp->next;
	}
	return (0);
}

char	**ft_seperate(char *str, char c)
{
	char	**matrix;
	size_t	a;

	a = 0;
	while (str[a] != c && str[a])
		a++;
	matrix = malloc(sizeof(char *) * 3);
	matrix[0] = ft_substr(str, 0, a);
	if (a < ft_strlen(str))
		matrix[1] = ft_substr(str, a, ft_strlen(str));
	return (matrix);
}

void	export_func(t_tree *branch, t_list **env)
{
	int		i;
	int		fd;
	t_list	*tenv;

	i = 0;
	if (branch->left)
	{
		if (branch->left->token == REDIRECAO)
		{
			fd = open(branch->left->left->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				printf("Error opening file\n");
		}
	}
	else
		fd = 1;
	if (!((char **)branch->token)[1])
	{
		declare_x(*env, fd);
		return ;
	}
	while (((char **)branch->token)[++i])
	{
		tenv = *env;
		if (ft_strchr(((char **)branch->token)[i], '=') && ft_strlen(
			ft_strchr(((char **)branch->token)[i], '=')) !=
			ft_strlen(((char **)branch->token)[i]))
			do_export(((char **)branch->token)[i], tenv, env);
		else
			ft_lstadd_back(env, ft_lstnew(((char **)branch->token)[i]));
	}
}

void	do_export(char *var, t_list *tenv, t_list **env)
{
	char	**tmp;
	char	*newvar;

	tmp = ft_seperate(var, '=');
	if (!exist_var(tenv, tmp[0]))
	{
		if (!tmp[1])
			newvar = ft_strdup(tmp[0]);
		else
			newvar = ft_strjoin(tmp[0], tmp[1]);
		ft_lstadd_back(env, ft_lstnew(newvar));
	}
	else
	{
		while (tenv)
		{
			if (!ft_strncmp(tenv->content, tmp[0], ft_strlen(tmp[0])))
			{
				free (tenv->content);
				tenv->content = ft_strjoin(tmp[0], tmp[1]);
			}
			tenv = tenv->next;
		}
	}
	free_matrix(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:56:24 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/22 14:43:38 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**find_path(t_list *env)
{
	char	**path;
	char	*tmp;
	t_list	*tenv;

	tenv = env;
	while (tenv)
	{
		if (!ft_strncmp(tenv->content, "PATH=", 5))
			tmp = ft_strdup(tenv->content + 5);
		tenv = tenv->next;
	}
	if (!tmp)
		return (NULL);
	path = ft_split(tmp, ':');
	return (path);
}

char	*get_path(t_tree *tree, t_list *env)
{
	char	*path;
	char	**paths;

	paths = find_path(env);
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		path = ft_strjoin(path, tree->token);
		if (!access(path, F_OK))
			return (path);
		paths++;
	}
	return (NULL);
}

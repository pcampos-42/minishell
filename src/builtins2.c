/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:25:51 by pcampos-          #+#    #+#             */
/*   Updated: 2022/07/21 11:24:51 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	exit_func(t_tree *branch, t_list **env)
//{
//	func_que_da_free_as_coisas();
//}

//falta testar
void	export_func(t_tree branch, t_list **env)
{
	char	**tmp;
	char	*newvar;

	tmp = ft_split(((char **)(branch.token))[1], '=');
	if ((tmp[1][0] == '"' && tmp[1][ft_strlen(tmp[1]) - 1] != '"') ||
		(tmp[1][ft_strlen(tmp[1]) - 1] == '"' && tmp[1][0] != '"'))
		ft_error();
	if (tmp[1][0] == '"' && tmp[1][ft_strlen(tmp[1]) - 1] == '"')
		tmp[1] = ft_strtrim(tmp[1], '"');
	tmp[0] = ft_strjoin(tmp[0], '=');
	newvar = ft_strjoin(tmp[0], tmp[1]);
	ft_lstadd_back(env, ft_lstnew(newvar));
	free (newvar);
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

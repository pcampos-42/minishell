/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:25:51 by pcampos-          #+#    #+#             */
/*   Updated: 2022/06/21 08:42:41 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_func(t_tree *branch, t_list **env)
{
	func_que_da_free_as_coisas();
}

void	export_func(t_tree *branch, t_list **env)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * ft_strlen(algo));
	ft_lstadd_back(env, ft_lstnew(tmp));
	free (tmp);
}

void	unset_func(t_tree *branch, t_list **env)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *env;
	while (tmp->next->content != algo && tmp->next != NULL)
		tmp = tmp->next;
	tmp2 = tmp;
	tmp = tmp->next;
	tmp2->next = tmp->next;
	ft_lstdelone(tmp, free);
}

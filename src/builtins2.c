/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:25:51 by pcampos-          #+#    #+#             */
/*   Updated: 2022/07/22 15:16:39 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	exit_func(t_tree *branch, t_list **env)
//{
//	func_que_da_free_as_coisas();
//}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:42:27 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/19 17:25:02 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	search_var(t_tree *branch, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	if (!ft_strncmp(tmp->content, ((char **)branch->token)[1],
		ft_strlen(((char **)branch->token)[1])))
		return (1);
	tmp = tmp->next;
	while (tmp->next != NULL)
	{
		if (!ft_strncmp(tmp->content, ((char **)branch->token)[1],
			ft_strlen(((char **)branch->token)[1])))
			return (2);
		tmp = tmp->next;
	}
	if (!ft_strncmp(tmp->content, ((char **)branch->token)[1],
		ft_strlen(((char **)branch->token)[1])))
		return (3);
	return (0);
}

t_list	*lstplast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

void	unset_mid(t_tree *branch, t_list *tmp, t_list *tmp2)
{
	while (ft_strncmp(tmp->next->content, ((char **)branch->token)[1],
		ft_strlen(((char **)branch->token)[1])))
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	ft_lstdelone(tmp2, free);
}

void	unset_func(t_tree *branch, t_list **env)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		pos;

	tmp = *env;
	tmp2 = NULL;
	pos = search_var(branch, env);
	if (pos == 1)
	{
		*env = (*env)->next;
		ft_lstdelone(tmp, free);
	}		
	if (pos == 3)
	{
		tmp = lstplast(*env);
		tmp2 = tmp->next;
		ft_lstdelone(tmp2, free);
		tmp->next = NULL;
		return ;
	}
	if (pos == 2)
	{
		unset_mid(branch, tmp, tmp2);
	}
	g_exit_status = 0;
}

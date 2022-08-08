/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:42:27 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/08 14:49:29 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_var(t_tree branch, t_list **env)
{
    t_list	*tmp;

    tmp = *env;
    if (!ft_strncmp(tmp->content, ((char **)branch.token)[1], ft_strlen(((char **)branch.token)[1])))
        return (1);
    tmp = tmp->next;
    while (tmp->next != NULL)
    {
        if (!ft_strncmp(tmp->content, ((char **)branch.token)[1], ft_strlen(((char **)branch.token)[1])))
            return (2);
        tmp = tmp->next;
    }
    if (!ft_strncmp(tmp->content, ((char **)branch.token)[1], ft_strlen(((char **)branch.token)[1])))
        return (3);
    else
        return (0);   
}

void	unset_func(t_tree branch, t_list **env)
{
	t_list	*tmp;
    t_list	*tmp2;
    int     pos;
	
    tmp = *env;
	pos = search_var(branch, env);
    if (pos == 0)
        return ;
    if (pos == 1)
        *env = (*env)->next;
    if (pos == 3)
    {
        tmp = ft_lstlast(*env);
        tmp = NULL;
        ft_lstdelone(tmp, free);
        return ;
    }
    if (pos == 2)
    {
        while (ft_strncmp(tmp->next->content, ((char **)branch.token)[1], ft_strlen(((char **)branch.token)[1])))
            tmp = tmp->next;
        tmp2 = tmp;
        tmp = tmp->next;
        tmp2->next = tmp->next;
    }

	ft_lstdelone(tmp, free);
}
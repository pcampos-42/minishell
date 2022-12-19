/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:15:49 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/19 17:19:16 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_update(t_list **env, char *str)
{
	free((*env)->content);
	(*env)->content = ft_strdup(str);
}

void	do_export(char *str, t_list **env)
{
	t_list	*tnv;

	tnv = *env;
	while (tnv)
	{
		if (!ft_strchr(str, '=') && !ft_strncmp((char *)tnv->content, str,
				ft_strlen((char *)tnv->content)))
			return (ft_update(&tnv, str));
		if (!ft_strncmp((char *)tnv->content, str,
				ft_strlen((char *)tnv->content)
				- ft_strlen(ft_strchr((char *)tnv->content, '='))))
		{
			if (!str[ft_strlen((char *)tnv->content)
					- ft_strlen(ft_strchr((char *)tnv->content, '='))])
				return ;
			if (str[ft_strlen((char *)tnv->content)
					- ft_strlen(ft_strchr((char *)tnv->content, '='))] == '=')
				return (ft_update(&tnv, str));
		}
		tnv = tnv->next;
	}
	ft_lstadd_back(env, ft_lstnew(ft_strdup(str)));
}

void	export_func(t_tree *branch, t_list **env, int fd)
{
	int		i;

	i = 0;
	if (!((char **)branch->token)[1])
		return (declare_x(*env, fd));
	while (((char **)branch->token)[++i])
		do_export(((char **)branch->token)[i], env);
	g_exit_status = 0;
}

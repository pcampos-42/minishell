/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:58:02 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/06 10:06:10 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_valid_path(t_tree branch)
{
    if (access(((char **)(branch.token))[1], F_OK) < 0)
	{
		printf("Can´t access %s\n", ((char **)(branch.token))[1]);
		return (1);
	}
    else
        return (0);
}

int	search_oldpwd(t_list *env)
{
	t_list *tmp;

	tmp = env;
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->content, "OLDPWD=/", 8))
			return (1);
		else
			tmp = tmp->next;
	}
	return (0);
}

void	cd_func(t_tree branch, t_list **env)
{
	t_list	*tmp;
	char	*pwd;

    if (check_valid_path(branch))
    {
        //func_error();
		printf("path invalido\n");
        return ;
    }
	pwd = getcwd(NULL, 0);
	tmp = *env;
	if (!search_oldpwd(tmp))
		ft_lstadd_back(env, ft_lstnew(ft_strjoin("OLDPWD=/", pwd)));
	else
	{
		while (tmp->next && ft_strncmp(tmp->content, "OLDPWD=/", 8) != 0)
			tmp = tmp->next;
	}
	(*env)->content = ft_strjoin("OLDPWD=/", pwd);
	if(chdir(((char **)(branch.token))[1]) == -1)
		printf("Deu merda\n");
	free (pwd);
	pwd = getcwd(NULL, 0);
	tmp = *env;
	while (ft_strncmp(tmp->content, "PWD=/", 5) != 0 && tmp->next)
		tmp = tmp->next;
	tmp->content = ft_strjoin("PWD=/", pwd);
	free (pwd);
}
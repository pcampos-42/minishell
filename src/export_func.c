/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 15:15:49 by pcampos-          #+#    #+#             */
/*   Updated: 2022/07/22 15:19:58 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//testado e aparentemente sem erros

char	**ft_seperate(char *str, char c)
{
	char	**matrix;
	int		a;

	a = 0;
	while(str[a] != c)
		a++;
	matrix = malloc(sizeof(char *) * 3);
	matrix[0] = ft_substr(str, 0, a + 1);
	matrix[1] = ft_substr(str, a + 1, ft_strlen(str));
	return (matrix);
}

void	export_func(t_tree branch, t_list **env)
{
	char	**tmp;
	char	*newvar;

	tmp = ft_seperate(((char **)(branch.token))[1], '=');
	newvar = ft_strjoin(tmp[0], tmp[1]);
	printf("%s\n\n", newvar);
	ft_lstadd_back(env, ft_lstnew(newvar));
}
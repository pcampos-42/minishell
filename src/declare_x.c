/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:57:46 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/16 15:21:03 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *put_quote(char *str)
{
    char    *new;
    char    *tmp;

    tmp = ft_strjoin("\"", str);
    new = ft_strjoin(tmp, "\"");
    free (tmp);
    return (new);
}

char	*prepare_quote(char *str)
{
	char	**matrix;
    char    *new;
	size_t	a;

	a = 0;
	while (str[a] != '=' && str[a])
		a++;
	matrix = malloc(sizeof(char *) * 3);
	matrix[0] = ft_substr(str, 0, a);
	if (a < ft_strlen(str))
		matrix[1] = put_quote(str + a);
    else
        matrix[1] = ft_strdup("\"\"");
    new = ft_strjoin(matrix[0], matrix[1]);
    free (matrix);
	return (new);
}

void	declare_x(t_list *env, int fd)
{
	t_list	*tenv;
	char	*tmp;

	tenv = env;
	while (tenv)
	{
		ft_putstr_fd("declare -x ", fd);
		if (!ft_strchr(tenv->content, '='))
			ft_putendl_fd(tenv->content, fd);
		else
        {
			tmp = prepare_quote(tenv->content);
            ft_putendl_fd(tmp, fd);
            free (tmp);
        }
		tenv = tenv->next;
	}
}
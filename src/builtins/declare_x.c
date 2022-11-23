/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:57:46 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/23 12:54:20 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	special_print(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
		ft_putchar_fd(str[i], fd);
	ft_putchar_fd(str[i], fd);
	ft_putchar_fd('\"', fd);
	while (str[++i])
		ft_putchar_fd(str[i], fd);
	ft_putchar_fd('\"', fd);
	ft_putchar_fd('\n', fd);
}

void	declare_x(t_list *env, int fd)
{
	t_list	*tenv;

	tenv = env;
	while (tenv)
	{
		ft_putstr_fd("declare -x ", fd);
		if (!ft_strchr(tenv->content, '='))
			ft_putendl_fd(tenv->content, fd);
		else
			special_print(tenv->content, fd);
		tenv = tenv->next;
	}
}

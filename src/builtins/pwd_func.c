/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:53:45 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/08 19:36:25 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd_func(t_tree *branch)
{
	char	*tmp;
	int		fd;

	if (branch->left)
	{
		if (branch->left->token == REDIRECAO)
		{
			fd = open(branch->left->left->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				printf("Error opening file\n");
		}
	}
	else
		fd = 1;
	if (fd < 0)
	{
		ft_putstr_fd("Error with comand: ", 2);
		ft_putendl_fd(((char **)(branch->token))[0], 2);
		return ;
	}
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	ft_putendl_fd(tmp, fd);
	free (tmp);
	if (fd > 2)
		close(fd);
}

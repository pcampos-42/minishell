/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:46:13 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/08 19:32:52 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo_func(t_tree *branch)
{
	int	fd;

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
	if (ft_strncmp(((char **)(branch->token))[1], "-n", 3))
		ft_putstr_fd(((char **)(branch->token))[1], fd);
	else
		ft_putendl_fd(((char **)(branch->token))[2], fd);
	if (fd > 2)
		close(fd);
}

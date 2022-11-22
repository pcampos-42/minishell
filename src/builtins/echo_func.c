/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:46:13 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/22 14:35:45 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo_func(t_tree *branch)
{
	int	fd;

	if (branch->left)
	{
		if (branch->left)
		{
			return ;
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
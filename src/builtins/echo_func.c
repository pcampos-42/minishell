/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:46:13 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/19 19:38:31 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_flag(t_tree *branch)
{
	int	i;

	i = 0;
	if (((char **)(branch->token))[1] == NULL ||
	!((char **)(branch->token))[1][0])
		return (0);
	if (((char **)(branch->token))[1][0] != '-')
		return (0);
	while (((char **)(branch->token))[1][++i])
	{
		if (((char **)(branch->token))[1][i] != 'n')
			return (0);
	}
	return (1);
}

void	echo_func(t_tree *branch, int fd)
{
	if (check_flag(branch))
		print_args(((char **)(branch->token)), fd, 2);
	else
		print_args_nl(((char **)(branch->token)), fd, 1);
	g_exit_status = 0;
}

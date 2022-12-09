/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:46:13 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/28 16:21:40 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	echo_func(t_tree *branch, int fd)
{
	if (!ft_strncmp(((char **)(branch->token))[1], "-n", 3))
		print_args(((char **)(branch->token)), fd, 2);
	else
		print_args_nl(((char **)(branch->token)), fd, 1);
}

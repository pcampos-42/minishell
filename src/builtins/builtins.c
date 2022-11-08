/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:38:09 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/08 19:24:17 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtins(t_tree *branch, t_list *env)
{
	if (!ft_strncmp(((char **)(branch->token))[0], "echo", 5))
		echo_func(branch);
	else if (!ft_strncmp(((char **)(branch->token))[0], "pwd", 4))
		pwd_func(branch);
	else if (!ft_strncmp(((char **)(branch->token))[0], "env", 3))
		env_func(*branch, env);
	else if (!ft_strncmp(((char **)(branch->token))[0], "cd", 3))
		cd_func(branch, &env);
	else if (!ft_strncmp(((char **)(branch->token))[0], "export", 7))
		export_func(branch, &env);
	else if (!ft_strncmp(((char **)(branch->token))[0], "unset", 6))
		unset_func(branch, &env);
}

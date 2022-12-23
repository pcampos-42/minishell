/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relative_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:31:13 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/23 14:36:51 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rp_util(char *cmd, char *path, char *tmp)
{
	path = getcwd(NULL, 0);
	tmp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (is_path(cmd, path))
		return (path);
	return (NULL);
}

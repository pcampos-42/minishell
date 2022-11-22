/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_treat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:34:48 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 12:19:57 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*treat_token(char *token, t_list *env)
{
	char	*home;

	if (!token)
		return (0);
	home = home_expand(token, env);
	if (home)
	{
		free_str(token);
		return (home);
	}
	else
		return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:40:49 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/05/15 19:27:34 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

int	count_tokens(char *s)
{
}

char	**lexer_main(char *s)
{
	char	*begin;
	char	*end;
	char	**tokens;
	int		c_tokens;

	c_tokens = count_tokens(s);
	tokens = malloc(2 * sizeof(char *));
	begin = ft_strchr(s, '"');
	if (begin)
	{
		end = ft_strchr(begin + 1, '"');
		if (!end)
			exit(EXIT_FAILURE);
		tokens[0] = malloc(ft_strlen(s) - ft_strlen(begin) + 1);
		ft_strlcpy(tokens[0], s, (ft_strlen(s) - ft_strlen(begin) + 1));
		tokens[1] = malloc(ft_strlen(begin) - ft_strlen(end) + 1);
		ft_strlcpy(tokens[1], begin + 1, ft_strlen(begin) - ft_strlen(end));
	}
	return (tokens);
}

int	main(void)
{
	char	str[100] = "cd \"hello world\" jkshdasj  hajskdhiuasg";

	lexer_main(str);
	return (0);
}

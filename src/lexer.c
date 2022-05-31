/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 19:40:49 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/05/31 11:57:21 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	count_matrix(char *s)
{
	int	i;
	int	flag;
	int	count;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{	
		if (s[i] == '|')
			break;
		 if (s[i] == ' ' && flag == 0 && s[i - 1] != '"' && s[i - 1] != '\'')
		 	count++;
		if ((s[i] == '"' || s[i] == '\'') && flag == 0)
		{
			flag = 1;
			count++;
		}
		else
			if ((s[i] == '"' || s[i] == '\'') && flag == 1)
				flag = 0;
		i++;
	}
	return (count);
}

void	create_token(t_tree **branch, char *s)
{
	int	size;

	size = count_matrix(s);
	printf("%d\n", size);
	//(*branch)->token = malloc((size + 1) * sizeof(char *));
	(void)branch;
}

t_tree	*lexer_main(char *s)
{
	t_tree	*tokens;

	tokens = NULL;
	create_token(&tokens, s);
	return (tokens);
}

int	main(void)
{
	char	str[100] = "cd \"hello world\" | jkshdasj | hajskdhiuasg";

	lexer_main(str);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:00:21 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 12:23:22 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

	/* Verificar se existe token
	Se nao existir terminou a string e entao retorno a tree
	Caso exista token
	Analisar e se tiver erro de syntax
		Retornar erro;
	Verificar o tipo de token;
	se o token for uma word fazer o tratamento antes do posicionamento dele na tree;
	Posicionamento do token na tree;
	Dar free ao token
	*/
t_tree	*parser_main(char *s, t_list *env)
{
	t_tree	*tree;
	int		reset;
	int		token_type;
	char	*token;

	reset = 1;
	tree = NULL;
	while (1)
	{
		token = get_token(s, reset);
		if (!token)
			break ;
		token_type = get_token_id(token);
		if (token_type == E_WORD)
			token = treat_token(token, env);
		build_tree(token, token_type, &tree);
		free_str(token);
		reset = 0;
	}
	return (tree);
}

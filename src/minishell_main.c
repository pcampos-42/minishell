/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/01 11:46:41 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	//char	*str;
	t_list	*env;
	t_tree	root;

	env = NULL;
	get_env(&env, envp);
	root.token = av;
	//printf("%s\n", ((char **)(root.token))[1]);
	//printf("%s\n", ((char **)(root.token))[2]);
	builtins(root, env);
	(void)ac;
	//(void)av;
	//(void)envp;
	//while (1)
	//{
	//	str = readline("CAREQUINHA_SHELL > ");
	//	printf("Linha recebida: %s\n", str);
	//	if (!(ft_strncmp(str, "exit", 4)))
	//	{
	//		free(str);
	//		rl_clear_history();
	//		return (0);
	//	}
	//	add_history(str);
	//	free(str);
	//}
	return (0);
}

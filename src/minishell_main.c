/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/22 14:33:43 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_list	*env;
	t_tree	*root;

	env = NULL;
	get_env(&env, envp);
	(void)ac;
	(void)av;
	while (1)
	{
		str = readline("GigaSHELL > ");
		if (!ft_strncmp(str, "exit", 5))
		{
			free(str);
			rl_clear_history();
			return (0);
		}
		add_history(str);
		root = parser_main(str, env);
		//exeggutor(&root, env);
		free(str);
		free_tree(root);
	}
	return (0);
}

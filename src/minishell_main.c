/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/05 11:26:56 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_list	*env;
	t_tree	root;

	env = NULL;
	get_env(&env, envp);
	(void)ac;
	(void)av;
	while (1)
	{
		str = readline("CAREQUINHA_SHELL > ");
		printf("Linha recebida: %s\n", str);
		if (!ft_strncmp(str, "exit", 4))
		{
			free(str);
			rl_clear_history();
			return (0);
		}
		add_history(str);
		if (ft_strchr(str, ' '))
			root.token = ft_split(str, ' ');
		else
			root.token = str;
		builtins(root, env);
		free(str);
	}
	return (0);
}

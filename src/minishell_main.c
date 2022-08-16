/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/08/16 15:19:50 by pcampos-         ###   ########.fr       */
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
		str = readline("MERDA_PA_ESTE_SHELL > ");
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
		{
			((char **)root.token)[0] = ft_strdup(str);
			((char **)root.token)[1] = NULL;
		}
		builtins(root, env);
		free(str);
	}
	return (0);
}

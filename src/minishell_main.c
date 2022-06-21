/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/06/21 08:04:51 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_list	*env;

	get_env(&env, envp);
	(void)ac;
	(void)av;
	while (1)
	{
		str = readline("CAREQUINHA_SHELL > ");
		printf("Linha recebida: %s\n", str);
		if (!(ft_strncmp(str, "exit", 4)))
		{
			free(str);
			rl_clear_history();
			return (0);
		}
		add_history(str);
		free(str);
	}
	return (0);
}

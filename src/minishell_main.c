/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/09 22:18:47 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	int		c;
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
		if (!str)
			break ;
		add_history(str);
		root = parser_main(str, env);
		c = 1;
		if (root->left)
		{
			c++;
			while (root->left->type == E_PIPE)
			{
				root = root->left;
				c++;
			}
		}
		exeggutor(&root, &env, c);
		free(str);
		free_tree(root);
	}
	rl_clear_history();
	if (env)
		ft_lstclear(&env, free);
	return (0);
}

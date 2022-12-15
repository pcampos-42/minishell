/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/15 21:25:02 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static int	skip_quotes(char *str, int *i)
{
	char	c;

	c = str[(*i)++];
	while (str[*i])
	{
		if (str[*i] == c)
			return (0);
		(*i)++;
	}
	return (1);
}	

static int	check_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|')
		return (1);
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]) && skip_quotes(str, &i))
			return (2);
		if (str[i] == '|' && str[i + 1] == '|')
			return (3);
		i++;
	}
	return (0);
}

void	main_util(t_tree *root, t_list *env)
{
	int	c;

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
}

void	print_error(int i)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (i != 2)
		ft_putstr_fd("|", STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

// 33 linhas tem o main
int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_list	*env;
	t_tree	*root;
	int		error;

	env = NULL;
	get_env(&env, envp);
	(void)ac;
	(void)av;
	while (1)
	{
		str = readline("GigaSHELL > ");
		if (!str)
			break ;
		if (ft_strlen(str) == 0)
		{
			free(str);
			continue ;
		}
		error = check_syntax(str);
		if (error)
		{
			print_error(error);
			free(str);
			g_exit_status = 2;
			add_history(str);
			continue ;
		}
		add_history(str);
		root = parser_main(str, env);
		main_util(root, env);
		free_tree(root);
		free(str);
	}
	rl_clear_history();
	if (env)
		ft_lstclear(&env, free);
	return (0);
}

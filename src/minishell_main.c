/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/16 02:10:35 by lucas-ma         ###   ########.fr       */
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

void	main_util(char *str, t_list **env)
{
	t_tree	*root;
	int		c;

	c = 1;
	root = parser_main(str, *env);
	if (!root)
	{
		free_str(str);
		return ;
	}
	if (root->left)
	{
		c++;
		while (root->left->type == E_PIPE)
		{
			root = root->left;
			c++;
		}
	}
	exeggutor(&root, env, c);
	free_str(str);
	free_tree(root);
}

void	print_error(int i)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (i == 2)
		ft_putstr_fd("\"", STDERR_FILENO);
	else if (i == 1 || i == 3)
		ft_putstr_fd("|", STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	make_readline(t_list **env)
{
	char	*str;

	while (1)
	{
		str = readline("GigaSHELL > ");
		if (!str)
			break ;
		if (ft_strlen(str) == 0)
		{
			g_exit_status = 0;
			free(str);
			continue ;
		}
		if (check_syntax(str))
		{
			print_error(check_syntax(str));
			g_exit_status = 2;
			add_history(str);
			free(str);
			continue ;
		}
		add_history(str);
		main_util(str, env);
	}	
}

// 33 linhas tem o main
int	main(int ac, char **av, char **envp)
{
	t_list				*env;
	struct termios		term;
	struct termios		term2;

	env = NULL;
	get_env(&env, envp);
	(void)ac;
	(void)av;
	(void)term;
	(void)term2;
	make_readline(&env);
	rl_clear_history();
	if (env)
		ft_lstclear(&env, free);
	return (0);
}

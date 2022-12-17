/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/17 05:28:51 by pcampos-         ###   ########.fr       */
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
		return ;
	if (root->left && !is_node_red(root->left))
	{
		c++;
		while (root->left->type == E_PIPE)
		{
			root = root->left;
			c++;
		}
	}
	exeggutor(&root, env, c);
	free_tree(root);
}

void	make_readline(t_list **env, struct termios *term, \
struct termios *term2)
{
	char	*str;

	while (1)
	{
		str = make_signals(term, *env, term2);
		if (ft_strlen(str) != 0)
		{
			add_history(str);
			if (check_syntax(str))
			{
				print_error(check_syntax(str));
				g_exit_status = 2;
				free(str);
				continue ;
			}
			main_util(str, env);
			free(str);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list				*env;
	struct termios		term;
	struct termios		term2;

	env = NULL;
	get_env(&env, envp);
	if (isatty(STDIN_FILENO) != 1 || !env)
	{
		if (env)
			ft_lstclear(&env, free);
		ft_putstr_fd("GigaSHELL: ", STDERR_FILENO);
		perror("attributes setting failed");
		exit(errno);
	}
	(void)ac;
	(void)av;
	prep_termios(&term, &term2, &env);
	
	make_readline(&env, &term, &term2);
	rl_clear_history();
	if (env)
		ft_lstclear(&env, free);
	return (0);
}

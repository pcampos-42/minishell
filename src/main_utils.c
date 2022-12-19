/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:22:57 by pcampos-          #+#    #+#             */
/*   Updated: 2022/12/17 07:22:56 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int i)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (i == 2)
		ft_putstr_fd("\"' or `'", STDERR_FILENO);
	else if (i == 1 || i == 3)
		ft_putstr_fd("|", STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	prep_termios(struct termios *term, struct termios *term2, t_list **env)
{
	if (tcgetattr(STDIN_FILENO, term) != 0)
	{
		ft_putstr_fd("GigaSHELL: ", STDERR_FILENO);
		perror("attributes setting failed");
		if (env)
			ft_lstclear(env, free);
		exit(1);
	}
	if (tcgetattr(STDIN_FILENO, term2) != 0)
	{
		ft_putstr_fd("GigaSHELL: ", STDERR_FILENO);
		perror("attributes setting failed");
		if (env)
			ft_lstclear(env, free);
		exit(1);
	}
	term->c_cc[VQUIT] = _POSIX_VDISABLE;
	term->c_lflag &= ~ECHOCTL;
}

void	attr_setting(struct termios *term, t_list **env)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term) != 0)
	{
		ft_putstr_fd("GigaSHELL: ", STDERR_FILENO);
		perror("attributes setting failed");
		if (env)
			ft_lstclear(env, free);
		exit(1);
	}
}

char	*make_signals(struct termios *term, t_list *env, struct termios *term2)
{
	char	*str;

	call_sigact(SI_RLINE, &env);
	attr_setting(term, &env);
	str = readline("GigaSHELL > ");
	if (!str)
	{
		attr_setting(term2, &env);
		free_str(str);
		if (env)
			ft_lstclear(&env, free);
		ft_putendl_fd("Exit", 2);
		exit(g_exit_status);
	}
	call_sigact(SI_IGN, &env);
	return (str);
}

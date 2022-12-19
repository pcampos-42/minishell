/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:14:20 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/19 19:24:31 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signals(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

static void	handle_signals_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "> \n", 3);
	}
}

static void	prep_act(struct sigaction *act, char si_mode)
{
	ft_memset(act, '\0', sizeof(*act));
	act->sa_flags = SA_SIGINFO;
	sigemptyset(&act->sa_mask);
	if (si_mode == SI_IGN)
		(act->sa_handler) = SIG_IGN;
	else if (si_mode == SI_HDOC)
		(act->sa_sigaction) = handle_signals_heredoc;
	else if (si_mode == SI_RLINE)
		(act->sa_sigaction) = handle_signals;
	else if (si_mode == SI_DFL)
		(act->sa_handler) = SIG_DFL;
	else
		return ;
}

void	call_sigact(char act_choice, t_list **env)
{
	struct sigaction	act;

	prep_act(&act, act_choice);
	if (sigaction(SIGQUIT, &act, NULL) == -1
		|| sigaction(SIGINT, &act, NULL) == -1)
	{
		ft_putstr_fd("GigaSHELL: ", STDERR_FILENO);
		perror("fatal");
		if (env)
			ft_lstclear(env, free);
		exit(1);
	}
}

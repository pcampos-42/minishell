/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 05:47:29 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/17 06:32:54 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_last_cmd(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (status < 130)
		{
			ft_putstr_fd("\n", STDERR_FILENO);
			g_exit_status = status + 128;
		}
		else
		{
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			g_exit_status = status;
		}
	}		
}

static void	wait_missing_cmds(int n_cmds, t_list *env)
{
	int	status;
	int	signal;

	signal = 0;
	n_cmds--;
	call_sigact(SI_IGN, &env);
	while (n_cmds)
	{
		wait(&status);
		if (WIFSIGNALED(status) && status == SIGINT)
		signal = 1;
		n_cmds--;
	}
	if (signal)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	wait_cmds(int last_pid, int n_cmds, t_list *env)
{
	wait_last_cmd(last_pid);
	wait_missing_cmds(n_cmds, env);
}

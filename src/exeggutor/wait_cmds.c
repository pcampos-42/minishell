/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 05:47:29 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/19 19:41:51 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	wait_last_cmd(int pid, t_list *env)
{
	int	status;

	call_sigact(SI_IGN, &env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_exit_status = 128 + status;
		if (g_exit_status == 130)
			ft_putchar_fd('\n', STDOUT_FILENO);
		else if (g_exit_status > 130)
		{
			ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
			g_exit_status = 131;
		}
	}
}

static void	wait_missing_cmds(int n_cmds)
{
	int	status;

	n_cmds--;
	while (n_cmds)
	{
		wait(&status);
			n_cmds--;
	}
}

void	wait_cmds(int last_pid, int n_cmds, t_list *env)
{
	wait_last_cmd(last_pid, env);
	wait_missing_cmds(n_cmds);
}

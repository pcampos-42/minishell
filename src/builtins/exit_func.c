/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:26:18 by pcampos-          #+#    #+#             */
/*   Updated: 2022/11/28 15:48:41 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_num(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (!n)
			n = 1;
		i++;
	}
	if (!str[i] && n)
		return (1);
	return (0);
}

void	go_buy_milk(t_tree *branch, int n)
{
	if (n && ((char **)(branch->token))[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_exit_status = 1;
		return ;
	}
	g_exit_status = 2;
	ft_putstr_fd("exit\nshell: exit ", 2);
	ft_putstr_fd(((char **)(branch->token))[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	//free_tree();
	rl_clear_history();
	exit(2);
	return ;
}

void	exit_func(t_tree *branch)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	if (((char **)(branch->token))[1] && is_num(((char **)(branch->token))[1]))
		n = 1;
	if ((n && !((char **)(branch->token))[2]) || !((char **)(branch->token))[1])
	{
		ft_putstr_fd("exit\n", 2);
		if (n)
		{
			g_exit_status = ft_atoi(((char **)(branch->token))[1]);
			rl_clear_history();
			exit(g_exit_status);
		}
		rl_clear_history();
		exit(g_exit_status);
	}
	return (go_buy_milk(branch, n));
}

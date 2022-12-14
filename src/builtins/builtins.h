/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/12 21:13:39 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//------------------------------INCLUDES------------------------------//
# include "../minishell.h"

//------------------------------BUILTINS------------------------------//
void	print_args(char **token, int fd, int i);
void	print_args_nl(char **token, int fd, int i);

//------------------------------PWD_FUNC------------------------------//
void	pwd_func(int fd);

//------------------------------ECHO_FUNC------------------------------//
void	echo_func(t_tree *branch, int fd);

//------------------------------EXPORT_FUNC------------------------------//
void	export_func(t_tree *branch, t_list **env, int fd);
char	**ft_seperate(char *str, char c);
void	do_export(char *str, t_list **env);
int		exist_var(t_list *env, char *name);

//------------------------------CD_FUNC------------------------------//
void	cd_func(t_tree *branch, t_list **env);
int		check_valid_path(t_tree *branch);
void	do_cd(t_tree *branch, t_list **env);

//------------------------------UNSET_FUNC------------------------------//
void	unset_func(t_tree *branch, t_list **env);
int		search_var(t_tree *branch, t_list **env);
t_list	*lstplast(t_list *lst);

//------------------------------DECLARE_X------------------------------//
void	declare_x(t_list *env, int fd);
char	*prepare_quote(char *str);
char	*put_quote(char *str);

//------------------------------EXIT_FUNC------------------------------//
void	exit_func(t_tree *branch);
int		is_num(char *str);
void	go_buy_milk(t_tree *branch, int n);

#endif
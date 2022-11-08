/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/08 19:24:50 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//------------------------------INCLUDES------------------------------//
# include "../minishell.h"

//------------------------------BUILTINS------------------------------//
void	builtins(t_tree *branch, t_list *env);

//------------------------------PWD_FUNC------------------------------//
void	pwd_func(t_tree *branch);

//------------------------------ECHO_FUNC------------------------------//
void	echo_func(t_tree *branch);

//------------------------------EXPORT_FUNC------------------------------//
void	export_func(t_tree *branch, t_list **env);
char	**ft_seperate(char *str, char c);
void	do_export(char *var, t_list *tenv, t_list **env);
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

#endif
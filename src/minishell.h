/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/08/02 11:13:01 by pcampos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//------------------------------INCLUDES------------------------------//
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

//------------------------------STRUCTS------------------------------//
typedef struct s_tree
{
	void			*token;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*parent;
}					t_tree;

//------------------------------TREE------------------------------//
void	tree_add_left(t_tree **root, t_tree *new);
void	tree_add_right(t_tree **root, t_tree *new);
void	tree_add_root(t_tree **root, t_tree *new_root);

//------------------------------ENV------------------------------//
void	get_env(t_list **env, char **envp);
void	print_env(t_list *env, int fd);
char	**env_matrix(t_list *env);

//------------------------------BUILTINS------------------------------//
void	builtins(t_tree branch, t_list *env);
void	echo_func(t_tree branch);
void	pwd_func(t_tree branch);
void	env_func(t_tree branch, t_list *env);
void	cd_func(t_tree branch, t_list **env);

//------------------------------BUILTINS2------------------------------//
void	unset_func(t_tree branch, t_list **env);

//------------------------------EXPORT_FUNC------------------------------//
void	export_func(t_tree branch, t_list **env);
char	**ft_seperate(char *str, char c);

//------------------------------CD_FUNC------------------------------//
void	cd_func(t_tree branch, t_list **env);
int 	check_valid_path(t_tree branch);

#endif

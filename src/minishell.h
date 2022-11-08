/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/08 19:38:44 by pcampos-         ###   ########.fr       */
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

//------------------------------ENV------------------------------//
void	get_env(t_list **env, char **envp);
void	print_env(t_list *env, int fd);
char	**env_matrix(t_list *env);
void	env_func(t_tree *branch, t_list *env);

//------------------------------FREE_FUNCS------------------------------//
void	free_matrix(char **matrix);

#endif

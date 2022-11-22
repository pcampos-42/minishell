/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcampos- <pcampos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/11/22 14:42:33 by pcampos-         ###   ########.fr       */
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
# include <sys/wait.h>

//------------------------------DEFINES------------------------------//
# define OPERATORS		"<>|"
# define WHITE_SPACE	" \t\r\n\v\f"

//------------------------------STRUCTS------------------------------//
typedef enum e_type
{
	E_WORD,
	E_CMD,
	E_PIPE,
	E_IN,
	E_OUT,
	E_APPEND,
	E_HDOC,
	E_BUILT
}	t_type;

typedef struct s_tree
{
	void			*token;
	int				type;
	int				p[2];
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
void	free_str(char *str);
void	free_tree(t_tree *tree);

//------------------------------BUILTINS------------------------------//
void	builtins(t_tree *branch, t_list *env);

//------------------------------EXEGGUTOR------------------------------//
void	exeggutor(t_tree **root, t_list *env);
void	finish_tree(t_tree *tree, t_list *env);
void	do_comand(t_tree *tree, t_list *env);
void	child_labor(t_tree *tree, t_list *env, int *pipe_fd);

//------------------------------REDIR------------------------------//

//------------------------------EXEC_UTILS------------------------------//
char	**find_path(t_list *env);
char	*get_path(t_tree *tree, t_list *env);

//------------------------------PARSER_MAIN-----------------------------//
t_tree	*parser_main(char *s, t_list *env);

//------------------------------PARSE_UTILS2---------------------------//
int		is_node_red(t_tree *node);
int		is_node_cmd(t_tree *node);
int		is_node_pipe(t_tree *node);

#endif

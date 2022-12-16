/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/12/16 17:35:10 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//------------------------------INCLUDES------------------------------//
# include "../minishell.h"

//------------------------------PARSER_MAIN-----------------------------//
t_tree	*parser_main(char *s, t_list *env);

//------------------------------PARSER_UTILS----------------------------//
int		ft_is(char c, char *s);
void	print_matrix(char **mat);
int		get_token_id(char *token);
char	*exist_in_env(char *elem, t_list *env);
void	*mem_guard(void *p);

//------------------------------PARSE_UTILS2---------------------------//
int		is_node_red(t_tree *node);
int		is_node_cmd(t_tree *node);
int		is_node_pipe(t_tree *node);

//------------------------------GET_TOKEN-------------------------------//
char	*get_token(char *s, int reset);

//------------------------------TOKEN_TREAT-----------------------------//
char	*treat_token(char *token, t_list *env);

//------------------------------HOME_EXPAND-----------------------------//
char	*home_expand(char *token, t_list *env);

//------------------------------BUILD_TREE------------------------------//
void	build_tree(char *token, int token_id, t_tree **tree);

//------------------------------TREE_UTILS------------------------------//
t_tree	*create_node(int type);
void	add_node_on_top(t_tree **tree, t_tree *new_node);
void	add_node_on_left(t_tree *current, t_tree *new_node);
void	add_node_on_right(t_tree *current, t_tree *new_node);

//------------------------------UPDATE_NODE-----------------------------//
t_tree	*update_node(t_tree *node, char *token);

//------------------------------UPDATE_TOKEN----------------------------//
char	*update_token(char *token, char *new_token, int *i, t_list *env);

//------------------------------ADD_NEW_NODES---------------------------//
void	add_new_node(t_tree **tree, t_tree *node);

//------------------------------EXPANDER--------------------------------//
char	*expand_str(char *s, t_list *env);

//------------------------------EXPANDER_UTILS--------------------------//
char	*token_join(char *s1, char *s2, int o);
char	*strjoin_char(char *str, char c);
t_list	*exist_env_var(t_list *env, char *var_name);

//------------------------------SYNTAX_ERROR----------------------------//
int		syntax_error(t_tree *tree, char *token);
int		error_analysis(t_tree *tree, char *token);
int		branch_analysis(t_tree *node);

#endif

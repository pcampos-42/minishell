/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:38:30 by lucas-ma          #+#    #+#             */
/*   Updated: 2022/05/27 11:39:26 by lucas-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_tree
{
	char			**token;
	int				type;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*parent;
}					t_tree;

void	tree_add_left(t_tree **root, t_tree *new);
void	tree_add_right(t_tree **root, t_tree *new);
void	tree_add_root(t_tree **root, t_tree *new_root);

#endif
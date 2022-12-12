# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 15:07:52 by lucas-ma          #+#    #+#              #
#    Updated: 2022/12/12 16:48:46 by lucas-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################ PROGRAM ################

NAME	    =    minishell

################ TERMINAL ###############

RMV        =        rm -f
MKD        =        mkdir
PRT        =        printf
MKE        =        make
CPY        =        cp

################# COLORS ################

--GRN    =        \033[32m
--RED    =        \033[31m
--WHT    =        \033[39m

################# DIRS ##################

_SRC    =        src/
_OBJ 	=		 obj/
_LIB    =        libs/
_BIN    =        ./

############### COMPILER ################

CC      =        gcc
CFLAGS      =        -Wall -Werror -Wextra #-g -fsanitize=address
SRCS    =        $(_SRC)minishell_main.c \
				 $(_SRC)free_funcs.c \
				 $(_SRC)env.c \
				 $(_SRC)builtins/builtins.c \
				 $(_SRC)builtins/cd_func.c \
				 $(_SRC)builtins/declare_x.c \
				 $(_SRC)builtins/echo_func.c \
				 $(_SRC)builtins/export_func.c \
				 $(_SRC)builtins/pwd_func.c \
				 $(_SRC)builtins/unset_func.c \
				 $(_SRC)builtins/exit_func.c \
				 $(_SRC)exeggutor/exeggutor.c \
				 $(_SRC)exeggutor/path_utils.c \
				 $(_SRC)exeggutor/relative_path.c \
				 $(_SRC)parser/parser_main.c \
				 $(_SRC)parser/add_new_nodes.c \
				 $(_SRC)parser/build_tree.c \
				 $(_SRC)parser/get_token.c \
				 $(_SRC)parser/home_expand.c \
				 $(_SRC)parser/parser_utils.c \
				 $(_SRC)parser/parser_utils2.c \
				 $(_SRC)parser/token_treat.c \
				 $(_SRC)parser/tree_utils.c \
				 $(_SRC)parser/update_node.c \
				 $(_SRC)redir/redir.c \
				 
OBJS    =        $(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))
DEPS    =        libft.a
LIBS    =        -lft -lreadline

################ RULES ##################

all: deps $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	@$(MKD) -p $(@D)
	$(CC) $(CF) -c $< -o $@

$(NAME): deps $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -L $(_LIB) $(LIBS)

################ DEPS ###################

deps: $(DEPS)

libft.a:
	$(MKE) bonus -C libft/

############## STRUCTURE ################

$(_OBJ):
	$(MKD) $(_OBJ)

$(_LIB):
	$(MKD) $(_LIB)

$(_SRC):
	$(MKD) $(_SRC)

$(_BIN):
	$(MKD) $(_BIN)libs/libft.a

fclean: clean
	$(RMV) -r $(NAME)
	$(RMV) -r $(_OBJ)
	$(RMV) -r $(_LIB)libft.a

re: fclean all

rebonus: fclean bonus

.PHONY: all deps clean fclean re

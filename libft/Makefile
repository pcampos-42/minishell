# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucas-ma <lucas-ma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:11:06 by lucas-ma          #+#    #+#              #
#    Updated: 2022/05/04 10:02:36 by lucas-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------ LIBRARY NAME ----------------------------------#

NAME	= libft.a

#----------------------------- COMMAND LINES ----------------------------------#

RM	= rm -rf
MV	= mv
MKD	= mkdir
CPY	= cp
PRINT	= printf

#------------------------------ DIRECTORIES -----------------------------------#

_SRC	=
_OBJ	=	../obj/
_LIBS	=	../libs/

#-------------------------------- COMPILER ------------------------------------#

CC	= gcc
CF	= -Wall -Wextra -Werror
AR	= ar rcs

#---------------------------------- FILES -------------------------------------#

FILES	= ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_memset.c ft_bzero.c ft_memmove.c ft_striteri.c \
			ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_itoa.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
			get_next_line.c get_next_line_utils.c
			
BONUS_FILES	= ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
			ft_lstnew.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c

SRCS	=		$(addprefix $(_SRC), $(FILES))
BONUS_SRCS	=	$(addprefix $(_SRC), $(BONUS_FILES))
OBJS	=		$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(SRCS))
BONUS_OBJS	=	$(patsubst $(_SRC)%.c,$(_OBJ)%.o,$(BONUS_SRCS))

#---------------------------------- RULES -------------------------------------#

all: $(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CF) -c $< -o $@

$(NAME): $(_LIBS) $(_LIBS)$(NAME)
$(_LIBS)$(NAME): $(_OBJ) $(OBJS)
	$(AR) $(_LIBS)$(NAME) $(OBJS)

bonus:	$(_LIBS) $(_LIBS)$(NAME) $(BONUS_OBJS)
			$(AR) $(_LIBS)$(NAME) $(BONUS_OBJS)

#---------------------------- DIRECTORIES CREATION ---------------------------#

$(_OBJ):
	$(MKD) $(_OBJ)

$(_LIBS):
	$(MKD) $(_LIBS)

$(_SRC):
	$(MKD) $(_SRC)

#---------------------------------- CLEAN ------------------------------------#

clean:
		@$(RM) $(_OBJ)$(OBJS)

fclean: clean
		@$(RM) $(_LIBS)$(NAME)

#---------------------------------- REST -------------------------------------#

re:	fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: narakely <narakely@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 14:54:25 by narakely          #+#    #+#              #
#    Updated: 2021/07/07 16:56:02 by narakely         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

NAME1	=	pipex_bonus

SRCS	=	ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c pipex_utils.c pipex.c

SRCS_BONUS	=	ft_putstr_fd.c ft_split.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c pipex_bonus_utils.c pipex_bonus.c gnl/get_next_line.c gnl/get_next_line_utils.c

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

OBJS	=	${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS}

$(NAME1):	${OBJS_BONUS}
			${CC} -o ${NAME1} ${OBJS_BONUS}

all:		${NAME}

clean:		
			${RM} ${OBJS}
			${RM} ${OBJS_BONUS}

fclean:		clean
			${RM} ${NAME}
			${RM} ${NAME1}

re:			fclean all

.PHONY:		all clean fclean re run
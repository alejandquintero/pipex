# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 21:16:55 by aquinter          #+#    #+#              #
#    Updated: 2024/03/02 18:50:10 by aquinter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

RM = rm -rf

CFLAGS = -Wextra -Werror -Wall #-fsanitize=address

SRC = 	src/utils/ft_bzero.c \
		src/utils/free_pipex.c \
		src/utils/ft_calloc.c \
		src/utils/ft_isascii.c \
		src/utils/ft_split.c \
		src/utils/ft_strncmp.c \
		src/utils/get_next_line.c \
		src/utils/get_next_line_utils.c \
		src/processes.c \
		src/pipex.c

OBJ = ${SRC:%.c=%.o}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re:	fclean all
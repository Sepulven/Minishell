# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 16:23:35 by asepulve          #+#    #+#              #
#    Updated: 2023/03/31 15:02:29 by asepulve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	libft.a

CC 			= 	cc

CFLAGS 		= 	-Wall -Wextra -Werror

RM 			= 	rm -f

SRC			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c\
				ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
				ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
				ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c\
				ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c\
				ft_strdup.c ft_striteri.c ft_strjoin.c ft_strjoinf.c ft_strlcat.c\
				ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c\
				ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c\
				ft_tolower.c ft_toupper.c ft_lstadd_front.c\
				ft_lstclear.c ft_lstdelone.c ft_lstite.c \
				ft_lstnew.c ft_lstsize.c get_next_line.c ft_printf.c ft_protectmatrix.c\
				ft_strcmp.c ft_iswhitespace.c
				
#ft_lstadd_back.c  ft_lstlast.c ft_lstmap.c

SRC_OBJ 	= 	${SRC:.c=.o}

all:		${NAME}
$(NAME):	${SRC_OBJ}
			@ar rcs ${NAME} ${SRC_OBJ}

clean:
			@${RM} ${SRC_OBJ} ${B_OBJ}

fclean:		clean
			@${RM} ${NAME}

re:			fclean ${NAME}

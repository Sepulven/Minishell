
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 14:26:54 by mvicente          #+#    #+#              #
#    Updated: 2023/04/27 23:54:24 by asepulve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 # > >> < * ? [ ] | ; [ ] || && ( ) & # $  << " '

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

EXPANDER_SRC	= expander.c utils_expander.c

LEXER_SRC		= lexer.c formatter.c utils_lexer_1.c command_to_tokens.c

PARSER_SRC		= env_utils.c free_parser.c heredoc.c parser.c\
				  utils_parser_1.c redirect_outf_inf.c redirect_append.c

EXECUTOR_SRC	= cd.c echo.c builtins.c pwd.c commands.c execution.c \
				  export.c pipes.c env.c exit.c print_export.c unset.c update_var.c aux_executor.c

UTILS_SRC		= data_output.c string_jumps.c utils_list_1.c __def_env.c utils_general_1.c \
				  validator.c frees.c get_com_number.c aux.c



SRC				= $(addprefix expander/,$(EXPANDER_SRC)) \
				  $(addprefix lexer/,$(LEXER_SRC)) \
				  $(addprefix parser/,$(PARSER_SRC)) \
				  $(addprefix executor/,$(EXECUTOR_SRC)) \
				  $(addprefix utils/,$(UTILS_SRC)) \
				  main.c

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

%.o: %.c
		@$(CC) $(CFLAGS) -c $^ -o $@

all:	$(NAME)	

$(NAME):	$(OBJ)
			@make -s -C libft
			@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

clean:
		@make clean -s -C libft
		@$(RM) $(OBJ)

v:
		@make -s
		valgrind --verbose --leak-check=full --show-leak-kinds=all ./minishell 2> valgrind.txt

run:
	./minishell

fclean:	clean
		@make fclean -s -C libft
		@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean
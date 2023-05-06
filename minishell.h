/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:06 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/06 23:12:47 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 1

# include "utils/utils.h"
# include "lexer/lexer.h"
# include "expander/expander.h"
# include "parser/parser.h"
# include "executor/executor.h"
# include "libft/libft.h"

# include "stdlib.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

int				check_words(char const *s);

void			command_one(int **fd, t_command_list *lst, int i);
void			command_final(int **fd, t_command_list *lst, int i);
void			command_middle(int **fd, t_command_list *lst, int i);

void			command(int **fd, t_command_list *lst, int i, int com);
int				do_fork(t_command_list *lst, int **id, int i, int com);
void			execute_one(t_command_list *lst);
void			execute(t_command_list *lst, int com);

int				get_num_words(char *str, char c);

void			do_dups(int fin, int fout, int fd_close);
t_command_list	*get_lst(t_command_list *lst, int i);
int				**create_pipes(int com);
void			free_pipes(int **id, int com);

t_command_list	*no_redirections(t_command_list *new, char **aux, char **paths);
t_command_list	*get_parameters(t_command_list *new, char **aux);
t_command_list	*redirections(t_command_list *new, char **aux, char **paths);
#endif
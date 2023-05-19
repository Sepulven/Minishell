/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:06 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/19 20:01:04 by asepulve         ###   ########.fr       */
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

int				check_words(char const *s);

void			command_one(int **fd, t_com_list *lst, int i);
void			command_final(int **fd, t_com_list *lst, int i);
void			command_middle(int **fd, t_com_list *lst, int i);

void			command(int **fd, t_com_list *lst, int i, int com);
int				do_fork(t_com_list *lst, int **id, int i, int com);
void			execute_one(t_com_list *lst, int com);
void			execute(t_com_list *lst, int com);

int				get_num_words(char *str, char c);

void			do_dups(int fin, int fout, int fd_close);
t_com_list		*get_lst(t_com_list *lst, int i);
int				**create_pipes(int com);
void			free_pipes(int **id, int com);

t_com_list		*no_redirections(t_com_list *new, char **aux, char **paths);
t_com_list		*get_parameters(t_com_list *new, char **aux);
t_com_list		*redirections(t_com_list *new, char **aux, char **paths);
#endif
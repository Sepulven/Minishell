/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:28:35 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 20:00:30 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H 1

# include "../libft/libft.h"

# include <signal.h>
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

// # define DEBUG1 write(1, "PING1\n", 7);
// # define DEBUG2 write(1, "PING2\n", 7);

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_command_list
{
	char					*command;
	char					*path;
	char					**param;
	int						inf;
	int						outf;
	struct s_command_list	*next;
}	t_com_list;

/*data_output.c*/
void				print_env(char **env);
void				print_lexer(char ***lexer);
void				print_char_matrix(char **matrix);
void				print_parser(t_com_list *parser);

/*frees.c*/
void				free_double(char **array);
void				free_lst(t_com_list *lst);
void				free_tokens(char ***tokens);

/*validator.c*/
int					validator(char **_line);
int					is_empty_to_next_pipe(char *str);

/*get_com_number.c*/
int					get_com_number(char *str);

/*formatter.c*/
char				*formatter(char *unformatted);
char				*ft_strjoin_free(char *s1, char *s2, char *opt);

/*utils_files.c*/
void				delete_heredoc_files(void);
char				*get_pathname(int index);
char				*take_avaible_filename(void);
void				delete_current_heredoc(int inf);
char				*take_current_pathname(void);

/*signals.c*/
void				handler_quit(int signal);
void				handler(int signal);

/* aux.c ! Funcoes libft alteradas ! */
char				*ft_substr_mini(char const *s, unsigned int start, \
					unsigned int end);
int					ft_strcmp_mini(char *a, char *b);
void				print_char_matrix(char **matrix);
char				**dup_env(char **envp);
void				free_envp(char **env);

/*__def_env.c*/
char				***env(void);
void				free_env(t_env *env);

int					**pid(void);

/*utils_list_1.c*/
void				__ft_lstadd_back(t_com_list **lst, t_com_list *new);
void				__ft_lstadd_env(t_env **env, t_env *new);
int					__ft_lstsize_env(t_env *lst);
t_env				*__ft_lstlast_env(t_env *env);
t_com_list			*__ft_lstlast(t_com_list *lst);

/*string_jumps.c*/
int					jump_quotes(char *str);
int					jump_str_out_quotes(char *str);
int					jump_white_spaces(char *str);

/*utils_lexer_1.c*/
int					ft_isredirects(char *str);
int					ft_jump_redirect_token(char *str);

/*utils_general_1.c*/
void				ft_swap(char *x, char *y);
int					check_words(char const *s);
#endif
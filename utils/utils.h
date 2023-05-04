/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:28:35 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/04 12:44:25 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H 1

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>

# define DEBUG1 write(1, "PING1\n", 7);
# define DEBUG2 write(1, "PING2\n", 7);

extern int	g_exit_s;

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
}	t_command_list;

/*data_output.c*/
void				print_env(char **env);
void				print_lexer(char ***lexer);
void				print_char_matrix(char **matrix);
void				print_parser(t_command_list *parser);

/*__def_env.c*/
char				***env(void);
void				free_env(t_env *env);

/*utils_list_1.c*/
void				__ft_lstadd_back(t_command_list **lst, t_command_list *new);
void				__ft_lstadd_env(t_env **env, t_env *new);
int					__ft_lstsize_env(t_env *lst);
t_env				*__ft_lstlast_env(t_env *env);
t_command_list		*__ft_lstlast(t_command_list *lst);

/*string_jumps.c*/
int					jump_quotes(char *str);
int					jump_str_out_quotes(char *str);
int					jump_white_spaces(char *str);

/*utils_general_1.c*/
void				ft_swap(char *x, char *y);
#endif
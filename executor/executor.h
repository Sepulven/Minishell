/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:11:12 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/15 16:51:22 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H 1

# include "../utils/utils.h"
# include "../libft/libft.h"
// # include "../parser/parser.h"
// # include "../minishell.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

/*aux.c*/
void			write_error(char *str, int status);
void			error_m(char *command, char *param, char *str, int s);
int				get_com(t_command_list *lst);
void			error_function(t_command_list *lst, int **fd, int status);
int             check_flags_one(char **param, char *command);
int             check_flags_two(char **param, char *command);

/*builtins.c*/
t_env			*do_node(int f, int i, t_env *node, char *str);
t_env			*create_node(char *str);
void			check_builtin(int **fd, t_command_list *lst, int com);
int				check_builtin_one(t_command_list *lst);

/*cd.c*/
void			command_cd(char **param, t_env *env);

/*commands.c*/
void			command_one(int **fd, t_command_list *node, int i);
void			command_final(int **fd, t_command_list *node, int i);
void			command_middle(int **fd, t_command_list *node, int i);
void			command(int **fd, t_command_list *lst, int i, int com);

/*echo.c*/
void			command_echo(char **param);

/*env.c*/
void			command_env(char **param);
void			initialize_env(t_env **new);
t_env			*get_env(void);

/*execution.c*/
int				do_fork(t_command_list *lst, int **id, int i, int com);
void			execute_one(t_command_list *lst, int com);
void			execute(t_command_list *lst, int com);

/*exit.c*/
void			command_exit(t_command_list *lst);

/*export.c*/
void			command_export(char **param);

/*pipes.c*/
void			do_dups(int fin, int fout, int fd_close);
t_command_list	*get_lst(t_command_list *lst, int i);
int				**create_pipes(int com);
void			free_pipes(int **id, int com);
void			close_pipes(int **id, int com);

/*print_export.c*/
void			printf_env(char **env);
void			print_env_order(t_env *env_lst, int num_var);

/*pwd.c*/
void			command_pwd(t_env *env_lst, char **param);

/*unset.c*/
void			command_unset(char **param);

/*update_var.c*/
t_env			*fetch_node(t_env *env_lst, char *name);
void			update_all(t_env *env_lst, char **envp);
void			update_var(t_env *env_lst, char *oldpwd);

#endif
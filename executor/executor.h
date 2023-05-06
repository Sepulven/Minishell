/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:11:12 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/06 21:24:58 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H 1

# include "../utils/utils.h"
# include "../libft/libft.h"
# include "../parser/parser.h"
# include "../minishell.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

/*execution.c*/
void			execute(t_command_list *lst, int com);
void			execute_one(t_command_list *lst);
int 			do_fork(t_command_list *lst, int **id, int i, int com);
void			command(int **fd, t_command_list *lst, int i, int com);

/*pipes.c*/
void			do_dups(int fin, int fout, int fd_close);
t_command_list	*get_lst(t_command_list *lst, int i);
int				**create_pipes(int com);
void			free_pipes(int **id, int com);

/*utils_env_1.c*/
void			initialize_env(t_env **new);
t_env			*get_env(void);

/*commands.c*/
void			command_one(int **fd, t_command_list *node, int i);
void			command_final(int **fd, t_command_list *node, int i);
void			command_middle(int **fd, t_command_list *node, int i);

/*builtins.c*/
void			check_builtin(t_command_list *lst);
int				check_builtin_one(t_command_list *lst);
void			command_cd(char **param, t_env *env);
void			update_env(char *s, char **envp, int flag);
void			update_all(t_env *env_lst, char **envp);
void			update_var(t_env *env_lst, char *oldpwd);
t_env			*create_node(char *str);
t_env			*fetch_node(t_env *env_lst, char *name);
void			command_pwd(t_env *env_lst);
void			command_env(char **param);
void			initialize_env(t_env **new);
void			printf_env(char **env);
void			print_env_order(t_env *env_lst, int num_var);
void			command_export(char **param);
int				ft_lstsize_env(t_env *lst);
void			command_unset(char **param, t_env *env_lst);
void			free_env(t_env *env);
void			command_exit(t_command_list *lst);
void			ft_putendl_fd(char *s, int fd);
void			error_m(char *command, char *param, char *str, int s);
void			command_echo(char **param);
void			write_error(char *str, int status);
void			error_function(t_command_list *lst, int **fd, int status);
#endif
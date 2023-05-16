/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:59:06 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/16 11:22:56 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H 1

# include "../libft/libft.h"
# include "../utils/utils.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

// PARSER UTILS //

/*parser_lexer_utils.c*/
int				pos_of_c_in_str(char *str, char *c);
void			initialize_lst(t_com_list **new);

// FIM PARSER UTILS //

/* !Funcoes libft alteradas ! */
char			*ft_substr_mini(char const *s, \
				unsigned int start, unsigned int end);
int				ft_strcmp_mini(char *a, char *b);

/*parser.c*/
t_com_list	*parser(char ***tokens, char **envp);
t_com_list	*get_node(char **command_token, char **paths, \
				int command_index);

/*redirect_outf_inf.c*/
int				redirect_inf(char *token);
int				redirect_outf(char *token);

/*redirect_append.c*/
int				append(char *token);

/*redirect_heredoc.c*/
int				heredoc(char *token, int command_index);

/*env_utils.c*/
char			**get_paths(char **envp);
char			*check_path(char **paths, char *command);

t_com_list	*here_doc(t_com_list *new, char **aux, int *i, int fd);
#endif
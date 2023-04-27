/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:19:48 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/27 11:56:21 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H 1

# include "../minishell.h"

/*expander.c*/
char	*get_env_value(char *var_name, char **envp);
char	*expander(char *str, char **envp);

#endif
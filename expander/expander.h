/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:19:48 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 02:45:38 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H 1

# include "../utils/utils.h"

/*expander.c*/
char	*expander(char *str);

/*utils_expander.c*/
char	*get_env_value(char *var_name, char **envp);
int		ft_isvar(char *str);
#endif
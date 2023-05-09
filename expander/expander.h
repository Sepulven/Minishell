/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:19:48 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/04 15:44:54 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H 1

# include "../utils/utils.h"

/*expander.c*/
char	*expander(char *str);

/*utils_expander.c*/
char	*get_env_value(char *var_name, char **envp);

#endif
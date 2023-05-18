/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:43:08 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 11:27:26 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H 1

# include "../utils/utils.h"
# include "../libft/libft.h"

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

/*lexer.c*/
size_t	count_tokens_in_command(char *str);
char	***lexer(char *str, size_t num);

/*command_to_tokens.c*/
char	**command_to_tokens(char *str);

#endif
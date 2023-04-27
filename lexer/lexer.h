/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:43:08 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/27 00:32:51 by asepulve         ###   ########.fr       */
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

/*formatter.c*/
char	*formatter(char *unformatted);
char	*ft_strjoin_free(char *s1, char *s2, char *opt);

/*utils_lexer_1.c*/
int		ft_isredirects(char *str);
int		ft_jump_redirect_token(char *str);

#endif
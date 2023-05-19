/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:44:54 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:10:00 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

size_t	count_tokens_in_command(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		i += ft_jump_redirect_token(&str[i]);
		i += jump_white_spaces(&str[i]);
		count++;
	}
	return (count);
}

static void	populate_command_tokens(char *str, char	***tokens, int *pipe, int i)
{
	char	*command;
	int		pipe_buff;

	pipe_buff = *pipe;
	command = ft_calloc(sizeof(char), i - pipe_buff + 1 + 1 - (str[i] == '|'));
	if (!command)
		return ;
	ft_strlcpy(command, &str[pipe_buff], \
	i - pipe_buff + 1 - (str[i] == '|') + 1);
	*tokens = command_to_tokens(command);
	*pipe = i + (str[i] == '|');
}

// * Aloco o array de matrizes// * Aloco o array de matrizes
/*
	* Quebra a nossa string recebida pelo prompt 
	* em um array de matrizes que seram então processadas para o parser.
	* cada command será uma matrix, que tera os seus tipos de tokens.
	* * Done by.: asepulve
*/
char	***lexer(char *str, size_t num)
{
	char	***tokens;
	int		i;
	int		j;
	int		pipe;

	tokens = ft_calloc(num + 1, sizeof (char **));
	if (!tokens)
		return (NULL);
	i = 0;
	j = 0;
	pipe = 0;
	while (str[i])
	{
		i += jump_quotes(&str[i]);
		if (str[i] == '|' || !str[i + 1])
			populate_command_tokens(str, &tokens[j++], &pipe, i);
		i += 1 - (str[i] == '\'' || str[i] == '"');
	}
	if (str)
		free(str);
	return (tokens);
}

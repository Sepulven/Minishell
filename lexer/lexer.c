/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:44:54 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/28 23:35:47 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

/*
	* Based on the command passed as a string, counts the number of tokens
	* within the command. The algo. is related to the quotes rules and 
	* tokens diviser. The beginning of the matrix creation.
	* Returns 0 in an invalid scenario, attention is it impossible to have 0 commands.
		* * Done by: Arthur Aguiar
*/
size_t	count_tokens_in_command(char *str)
{
	int		i;
	size_t	counter;

	i = 0;
	counter = 1;
	i += jump_white_spaces(&str[i]);
	if (str[i] || ft_isredirects(&str[i]))
		i += ft_jump_redirect_token(&str[i]);
	else
		counter = 0;
	while (str[i])
	{
		i += jump_quotes(&str[i]);
		if (str[i] && (ft_iswhitespace(str[i]) || ft_isredirects(&str[i])))
		{
			i += jump_white_spaces(&str[i]);
			if (!str[i])
				break ;
			i += ft_jump_redirect_token(&str[i]);
			counter++;
		}
		else
			i++;
	}
	return (counter);
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

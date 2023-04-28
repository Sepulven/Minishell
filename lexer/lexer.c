/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:44:54 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/28 18:17:55 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

/*
	* Receives the token address, where it starts and ends.
	* Create the token based on the rules. Add quotes.
	* Return te token if the process works, and NULL if it doesn't;
*/
static char	*create_token(char *str, int start, int end)
{
	char	*token;
	char	*formatted;
	int		i;

	token = ft_calloc(end - start + 3, sizeof (char));
	if (!token)
		return (NULL);
	i = 0;
	while (i <= end - start)
	{
		token[i] = str[start + i];
		i++;
	}
	formatted = formatter(token);
	token = ft_calloc(ft_strlen(formatted) + 3, sizeof (char));	// * Devo obrigatoriamente deixar espaços para as aspas e o NULL;
	if (!token)
	{
		free(formatted);
		return (NULL);
	}
	ft_strlcat(token, "\"", 2);
	ft_strlcat(token, formatted, ft_strlen(formatted) + 2);
	ft_strlcat(token, "\"", ft_strlen(formatted) + 3);
	i = ft_isredirects(&token[1]);
	ft_swap(&token[0], &token[i]);
	free(formatted);
	return (token);
}

/*
	* Receives the str, the previous diviser position and the current diviser position.
	* Populates the the command_tokens through the rules and update the previous and current diviser.
*/
static void	populate_token(char *str, char *tokens, int *i, int *__token)
{
	(void)tokens;
	while (str[*i] && !ft_iswhitespace(str[*i]) && !ft_isredirects(&str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
			*i += jump_quotes(&str[*i]);
		else
			*i += 1 - (str[*i] == '\'' || str[*i] == '"');
	}
	if (*__token != *i)
		tokens = create_token(str, *__token, \
		*i - (!!ft_isredirects(&str[*i])));
	*__token = *i;
	*i += jump_white_spaces(&str[*i]);
	*i += ft_isredirects(&str[*i]);
	*i += jump_white_spaces(&str[*i]);
}

// * Enquanto não for um divisor, eu movo.
// * Neste cenario, significa que o diviser foi o ultimo local em que paramos e possui outro diviser
// * cenário a onde possuimos os quotes seguidos.

/*
	* Recebe a string no começo do comando e o seu tamanho
	* Retorna uma matrix com os tokens do comando ou NULL caso falhe.
	* a range do comando. Convertendo para uma matrix com os tokens.
	* Observação: Neste cenário a função continua a funcionar, entretanto não deve chegar aqui.
		* (test <<<< a e test <<<<a)
	* * Done by: Arthur Aguiar
*/
static char	**command_to_tokens_delete(char *str)
{
	int		i;
	int		j;
	int		__token;
	size_t	number_tokens;
	char	**command_tokens;

	if (!str)
		return (NULL);
	number_tokens = count_tokens_in_command(str);
	command_tokens = ft_calloc(number_tokens + 1, sizeof (char *));
	if (!command_tokens)
		return (NULL);
	i = 0;
	j = 0;
	__token = 0;
	i += jump_white_spaces(&str[i]);
	while (str[i])
	{
		populate_token(str, command_tokens[j], &i, &__token);
		if (command_tokens[j])
			j++;
	}
	if (str)
		free(str);
	return (command_tokens);
}

static char	**command_to_tokens(char *str)
{
	int		i;
	int		j;
	int		__token;
	size_t	number_tokens;
	char	**command_tokens;

	(void)command_to_tokens_delete;
	if (!str)
		return (NULL);
	number_tokens = count_tokens_in_command(str);
	command_tokens = ft_calloc(number_tokens + 1, sizeof (char *));
	if (!command_tokens)
		return (NULL);
	i = 0;
	j = 0;
	__token = 0;
	i += jump_white_spaces(&str[i]);
	while (str[i])
	{
		while (str[i] && !ft_iswhitespace(str[i]) && !ft_isredirects(&str[i]))
		{
			if (str[i] == '"' || str[i] == '\'')
				i += jump_quotes(&str[i]);
			else
				i += 1 - (str[i] == '\'' || str[i] == '"');
		}
		if (__token != i)
			command_tokens[j++] = create_token(str, __token, i - (!!ft_isredirects(&str[i])));
		__token = i; // * Movo pelos divisor até encontrar
		i += jump_white_spaces(&str[i]);
		i += ft_isredirects(&str[i]);
		i += jump_white_spaces(&str[i]);
	}
	if (str)
		free(str);
	return (command_tokens);
}


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
	counter = 0;
	i += jump_white_spaces(&str[i]);
	if (str[i] || ft_isredirects(&str[i]))
	{
		i += ft_jump_redirect_token(&str[i]);
		counter = 1;
	}
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
	char	*command;
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
		{
			// TODO: Pay attention to right here we needed to
			command = ft_calloc(sizeof(char), i - pipe + 1 + 1 - (str[i] == '|')); // * + (str[i] != '|')
			if (!command)// TODO: Free the memory in the worst scenario
				return (NULL);
			ft_strlcpy(command, &str[pipe], i - pipe + 1 - (str[i] == '|') + 1);
			tokens[j++] = command_to_tokens(command);
			pipe = i + (str[i] == '|');
		}
		i += 1 - (str[i] == '\'' || str[i] == '"');
	}
	if (str)
		free(str);
	return (tokens);
}

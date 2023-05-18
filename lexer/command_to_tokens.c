/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:04:28 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 14:29:20 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

/*
	* Receives the token address, where it starts and ends.
	* Create the token based on the rules. Add quotes.
	* Return the token if the process works, and NULL if it doesn't;
*/
static char	*create_token(char *str, int start, int end)
{
	char	*token;

	start += jump_white_spaces(&str[start]);
	if (ft_isredirects(&str[start]))
	{
		token = ft_calloc(ft_jump_redirect_token(&str[start]) + 1, 1);
		if (!token)
			return (NULL);
		ft_strlcpy(token, &str[start], ft_jump_redirect_token(&str[start]) + 1);
	}
	else
	{
		token = ft_calloc(end - start + 1, sizeof (char));
		if (!token)
			return (NULL);
		ft_strlcpy(token, &str[start], end - start + 1);
	}
	return (token);
}

/*static char	**command_to_tokens_util(char **command_tokens, char *str, \
			int __token, int *j)
{
	int		i;

	i = 0;
	i += jump_white_spaces(&str[i]) - (i > 0 && !ft_iswhitespace(str[i]));
	i += ft_isredirects(&str[i]);
	i += jump_white_spaces(&str[i]);
	while (str[i])
	{
		while (str[i] && !ft_iswhitespace(str[i]) \
			&& !ft_isredirects(&str[i]))
		{
			if (str[i] == '"' || str[i] == '\'')
				i += jump_quotes(&str[i]);
			else
				i += 1 - (str[i] == '\'' || str[i] == '"');
		}
		if (__token != i)
			command_tokens[(*j)++] = create_token(str, __token, i);
		__token = i;
		i += jump_white_spaces(&str[i]);
		i += ft_isredirects(&str[i]);
		i += jump_white_spaces(&str[i]);
	}
	return (command_tokens);
}*/

static char	**command_to_tokens_util(char **command_tokens, char *str, \
			int __token, int *j)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i += ft_jump_redirect_token(&str[i]);
		i += jump_white_spaces(&str[i]);
		command_tokens[(*j)++] = create_token(str, __token, i);
		__token = i;
	}
	return (command_tokens);
}

char	**command_to_tokens(char *str)
{
	size_t	number_tokens;
	char	**command_tokens;
	int		j;

	j = 0;
	if (!str)
		return (NULL);
	number_tokens = count_tokens_in_command(str);
	command_tokens = ft_calloc(number_tokens + 1, sizeof (char *));
	if (!command_tokens)
		return (NULL);
	command_tokens = command_to_tokens_util(command_tokens, str, 0, &j);
	if (str)
		free(str);
	return (ft_protectmatrix(command_tokens, j));
}

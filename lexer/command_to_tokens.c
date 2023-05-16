/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_to_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:04:28 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/16 20:41:06 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer.h"

/*
	* Receives the token address, where it starts and ends.
	* Create the token based on the rules. Add quotes.
	* Return te token if the process works, and NULL if it doesn't;
	! Todo: There is an error with the redirects, when I change the sides
*/
static char	*create_token(char *str, int start, int end)
{
	char	*token;
	char	*formatted;
	int		flag;

	flag = ft_isredirects(&str[start + jump_white_spaces(&str[start])]);
	// ft_printf("flag %d str[%s]\n", flag, &str[start]);
	token = ft_calloc(end - start + 3, sizeof (char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, &str[start], end - start + 1);
	formatted = formatter(token);
	token = ft_calloc(ft_strlen(formatted) + 3, sizeof (char));
	if (!token)
	{
		free(formatted);
		return (NULL);
	}
	ft_strlcat(token, "\"", 2);
	ft_strlcat(token, formatted, ft_strlen(formatted) + 2);
	ft_strlcat(token, "\"", ft_strlen(formatted) + 3);
	if (flag)
		ft_swap(&token[0], &token[flag]);
	free(formatted);
	return (token);
}

static char	**command_to_tokens_util(char **command_tokens, char *str, \
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:23:07 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/09 15:18:25 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"
// > >> << < * ? [ ] | ; || && ( ) & # $ " '

// Allowed characters: > >> < << " '
// | & ; < > ( ) $ ` \ ' " whitespaces # * ?

static int	isallowed(char c)
{
	return (!(c == '*' || c == '\\' || c == '#' || c == '`' \
			|| c == '&' || c == ';' || c == '(' || c == ')'));
}

/*
	Verifica pipes vazios e unclosed pipes;
	Verifico se é redirect;
	Verifico se o proximo caractere é outro redirect no mesmo sentido;
	Caso não olho o que se segue se é allowed menos pipe ou redirect, apos saltar o whitespaces.
	Para verificar se é os redirects são válidos.
*/
static int	repeat_out_rule(char *c)
{
	int	i;

	i = 0;
	// Tenho de verificar cada grupo de caractere individualmente. < > << >>
	if (!ft_strncmp(c, ">>", 2) || !ft_strncmp(c, "<<", 2))
	{
		i += jump_white_spaces(&c[2]) + 2;
		return (!isallowed(c[i]) || c[i] == '<' || c[i] == '>');
	}
	else if (c[i] == '<' || c [i] == '>')
	{
		i += jump_white_spaces(&c[1]) + 1;
		return (!isallowed(c[i]) || c[i] == '<' || c[i] == '>');
	}
	return (0);
}

void	err(char *msg, char *str, char c, int pos)
{
	ft_putstr_fd(msg, 2);
	ft_putnbr_fd(pos, 2);
	ft_putchar_fd(':', 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	free(str);
	exit(EXIT_FAILURE);
}

int	is_empty_to_next_pipe(char *str)
{
	int	i;

	i = 0 + (str[0] == '|');
	while (str[i] && str[i] != '|')
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validator(char **_line)
{
	int		i;
	char	*buff;
	char	*line;

	buff = ft_strtrim(*_line, " \n\t\r\f");
	free(*_line);
	*_line = ft_strtrim(buff, "|");
	if (ft_strncmp(*_line, buff, ft_strlen(buff)))
		err("Unclosed pipes.", *_line, '|', 0);
	free(buff);
	i = 0;
	line = *_line;
	while (line[i])
	{
		i += jump_quotes(&line[i]);
		if (!isallowed(line[i]) || repeat_out_rule(&line[i]))
			err("Unexpected character\n", line, line[i], i);
		if (line[i] == '|' && is_empty_to_next_pipe(&line[i]))
			err("Empty pipes.", line, line[i], i);
		i += 1 - (line[i] == '\'' || line[i] == '"');
	}
	return (1);
}

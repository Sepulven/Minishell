/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:23:07 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:11:06 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"
// * Aloco o array de matrizes// * Aloco o array de matrizes
/*
	* Quebra a nossa string recebida pelo prompt 
	* em um array de matrizes que seram então processadas para o parser.
	* cada command será uma matrix, que tera os seus tipos de tokens.
	* * Done by.: asepulve
*/
extern int	g_exit_s;

static int	isallowed(char c)
{
	return (!(c == '*' || c == '\\' || c == '#' || c == '`' \
			|| c == '&' || c == ';' || c == '(' || c == ')' ));
}

static int	repeat_out_rule(char *c)
{
	int	i;

	i = 0;
	if (!ft_strncmp(c, ">>", 2) || !ft_strncmp(c, "<<", 2))
	{
		i += jump_white_spaces(&c[2]) + 2;
		return (!isallowed(c[i]) || c[i] == '<' \
		|| c[i] == '>' || c[i] == '|' || c[i] == '\0');
	}
	else if (c[i] == '<' || c [i] == '>')
	{
		i += jump_white_spaces(&c[1]) + 1;
		return (!isallowed(c[i]) || c[i] == '<' \
		|| c[i] == '>' || c[i] == '|' || c[i] == '\0');
	}
	return (0);
}

int	err(char *msg, char **str, char c, int pos)
{
	ft_putstr_fd(msg, 2);
	ft_putnbr_fd(pos, 2);
	ft_putchar_fd(':', 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	if (*str)
		free(*str);
	*str = NULL;
	g_exit_s = EXIT_FAILURE;
	return (EXIT_FAILURE);
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

int	validator(char **str)
{
	int		i;
	char	*line;

	line = ft_strtrim(*str, " \n\t\r\f");
	free(*str);
	*str = line;
	if (line && (line[0] == '|' || line[ft_strlen(line) - 1] == '|'))
		return (err("Unclosed pipes.", &line, '|', 0));
	i = 0;
	while (line && line[i])
	{
		if (jump_quotes(&line[i]) < 0)
			return (err("Unclosed quotes", &line, line[i], i));
		i += jump_quotes(&line[i]);
		if (!line[i])
			break ;
		if (line[i] && (!isallowed(line[i]) || repeat_out_rule(&line[i])))
			return (err("Unexpected character\n", &line, line[i], i));
		else if (line[i] && (line[i] == '|' && is_empty_to_next_pipe(&line[i])))
			return (err("Empty pipes.", &line, line[i], i));
		i += 1 - (line[i] == '\'' || line[i] == '"');
	}
	return (0);
}

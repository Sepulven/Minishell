/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_jumps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:52:41 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 16:26:04 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "./utils.h"

extern int	g_exit_s;

/*
	* Retorna a quantidade de casa que deve ser percorrida até encontrar
	* a outra aspa igual.
*/

int	jump_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (str[i] != '\'' && str[i] != '"')
		return (0);
	c = str[i++];
	while (str[i])
	{
		if (str[i++] == c)
			return (i);
	}
	return (-10);
}

int	jump_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	return (i);
}

int	jump_str_out_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'' \
	&& str[i] != '"' && !ft_iswhitespace(str[i]))
		i++;
	return (i);
}

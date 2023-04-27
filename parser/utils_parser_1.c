/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:01:55 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/27 14:45:11 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"

int	pos_of_c_in_str(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (&str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// TODO: Remove it! Basicamente esta verificando se encontra vazio entre pipes;
int	check_words(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}


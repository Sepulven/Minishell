/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:01:55 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/16 11:22:56 by mvicente         ###   ########.fr       */
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

void	initialize_lst(t_com_list **new)
{
	(*new)->command = 0;
	(*new)->param = ft_calloc(1, sizeof (char *));
	(*new)->param[0] = NULL;
	(*new)->inf = 0;
	(*new)->outf = 0;
	(*new)->next = 0;
}

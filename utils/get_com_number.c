/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_com_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:47:26 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 14:24:51 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

int	get_com_number(char *str)
{
	int		com;
	int		i;

	i = 0;
	com = 1;
	while (str[i])
	{
		i = i + jump_quotes(&str[i]);
		if (str[i] == '|')
			com++;
		i += 1 - (str[i] == '\'' || str[i] == '"');
	}
	return (com);
}

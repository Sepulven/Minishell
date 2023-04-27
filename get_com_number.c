/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_com_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:47:26 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/27 16:03:43 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	is_empty_to_next_pipe(char *str)
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

static int	isforbiddenc(char c)
{
	return (c == ';' || c == '&');
}


/*
TODO: Quebrar esta função em dois, esta validando, alterando a string, e contando os comandos;
	* Ao em vez de dar exit quero mostrar a mensagem de erro e dar uma return
	* da quantidade de comandos.
	* Ja que no bash convencional, ele executa enquanto a estrutura estiver correta.
*/
int	get_com_number(char **unvalidated)
{
	int		com;
	int		i;
	char	*str;

	str = *unvalidated;
	i = 0;
	com = 1;
	while (str[i])
	{
		i = i + jump_quotes(&str[i]);
		if (isforbiddenc(str[i]))
		{
			ft_printf("SYNTAX ERROR; You can't have (%c) character not in between quotes.\n", str[i]);
			exit(EXIT_FAILURE);
		}
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				ft_printf("SYNTAX ERROR: Multiple pipes\n");
				exit(EXIT_FAILURE);
			}
			else if (str[i + 1] != '|')
			{
				if (is_empty_to_next_pipe(&str[i]))
				{
					ft_printf("SYNTAX ERROR: empty between pipes\n");
					exit(EXIT_FAILURE);
				}
				else
					com++;
			}
		}
		i += 1 - (str[i] == '\'' || str[i] == '"'); // * Caso for uma aspas eu não posso pular a frente pois tenho de de ter elas em pares.
	}
	*unvalidated = str;
	return (com);
}
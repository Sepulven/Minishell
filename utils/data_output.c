/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:12:07 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/16 11:22:56 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("\n\n");
}

void	print_lexer(char ***lexer)
{
	int	i;

	i = 0;
	while (lexer[i])
	{
		print_char_matrix(lexer[i]);
		i++;
	}
}

void	print_char_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		ft_printf("[%d]%s\n", i, matrix[i]);
		i++;
	}
}

void	print_parser(t_com_list *parser)
{
	int	i;
	int	j;

	j = 0;
	while (parser)
	{
		i = 0;
		ft_printf("[%d]Command: %s\n", j, parser->command);
		while (parser->param[i])
		{
			ft_printf("		PARAM[%d]:%s\n", i, parser->param[i]);
			i++;
		}		
		ft_printf("\nPATH: %s\n", parser->path);
		ft_printf("INFILE: %d 	OUTFILE: %d\n", parser->inf, parser->outf);
		j++;
		parser = parser->next;
	}
}

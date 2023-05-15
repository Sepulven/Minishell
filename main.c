/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:09 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/15 15:15:22 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <signal.h>
#include <stdlib.h>

int g_exit_s;

/*
 * Executa o processo convencional do bash, seguro.
 * Expander -> Lexer -> Parser -> Executor
 * Desta forma temos uma segurança quanto a modulirização
 */
static void	minishell(char *str)
{
	t_command_list	*parser_list;
	char			***tokens;
	int				com;

	validator(&str);
	com = get_com_number(str);
	str = expander(str);
	tokens = lexer(str, com);
	parser_list = parser(tokens, *env());
	if (!parser_list)
		return ;
	if (parser_list && parser_list->command)
		execute(parser_list, com);
	free_lst(parser_list);
}

/*
	! Don't delete it !
	Readline context useful:
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	// str = readline("ARTEZA:"); // readline for the evaluation
*/

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	str = NULL;
	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	*env() = dup_env(envp);
	while (1)
	{
		ft_printf("ARTEZA:");
		str = get_next_line(0);
		if (!str)
		{
			free_double(*env());
			ft_printf("\n");
			exit(EXIT_FAILURE);
		}
		else
			str[ft_strlen(str) - 1] = 0;
		minishell(str);
	}
}

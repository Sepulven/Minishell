/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:09 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/10 15:08:29 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <signal.h>
#include <stdlib.h>

int	g_exit_s;

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

// void	handler(int signal, siginfo_t *si, void *data)
// {
// 	(void)si;
// 	(void)data;
// 	ft_printf("\nSIGNAL[%d]\n", signal);
// }

// int	set_signals(void)
// {
// 	struct sigaction	act;

// 	act.sa_sigaction = handler;
// 	act.sa_flags = SA_SIGINFO;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGUSR1, &act, NULL);
// 	return (1);
// }

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	str = NULL;
	(void)argc;
	(void)argv;
	// set_signals();
	*env() = dup_env(envp);
	while (1)
	{
		// ft_printf("ourshell> ");
		str = get_next_line(0);
		str[ft_strlen(str) - 1] = '\0';
		minishell(str);
	}
}

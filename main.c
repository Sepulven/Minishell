/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:09 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/15 15:07:34 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
// 	ft_printf("SIGNAL[%d]\n", signal);
// }
// static int	sethandler(void)
// {
// 	struct sigaction	act;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:09 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/07 14:10:44 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	g_exit_s;
/*
	* Executa o processo convencional do bash, seguro.
	* Expander -> Lexer -> Parser -> Executor
	* Desta forma temos uma segurança quanto a modulirização
*/

void	minishell(char *str)
{
	t_command_list	*parser_list;
	char			***tokens;
	int				token_num;
	int				com;

	validator(str);
	com = get_com_number(str);
	str = expander(str);
	token_num = count_tokens_in_command(str);
	tokens = lexer(str, token_num);
	parser_list = parser(tokens, *env());
	if (!parser_list)
		return ;
	if (parser_list && parser_list->command)
		execute(parser_list, com);
	free_lst(parser_list);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	str = NULL;
	(void)argc;
	(void)argv;
	*env() = dup_env(envp);
	while (1)
	{
<<<<<<< HEAD
		// ft_printf("myshell:> ");
		str = get_next_line(0);
		str[ft_strlen(str) - 1] = '\0';
		minishell(str);
		add_history(str);
=======
		str = get_next_line(0);
		str[ft_strlen(str) - 1] = '\0';
		minishell(str);
>>>>>>> re_struct_project
	}
}

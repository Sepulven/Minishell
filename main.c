/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:09 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/08 14:04:40 by mvicente         ###   ########.fr       */
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

/*
	TODO: Dado a organização não quero ter no root do projeto nenhum outro ficheiro que não seja a main.
	TODO: Quando temos uma variavel de ambiente que nao existe substitui por "", quando passamos pelo lexer que realiza a tokenização ele vai colocar esta string nula entre parentese, corrigir isso.
		* acasd $PATHasdf ola
		* dentro
		* [0]"acasd"
		* [1]""
		* [2]"ola"
	* A solução para o problema é simples.
*/
int	main(int argc, char **argv, char **envp)
{
	char	*str;

	str = NULL;
	(void)argc;
	(void)argv;
	*env() = dup_env(envp);
	while (1)
	{
		ft_printf("myshell:> ");
		str = get_next_line(0);
		str[ft_strlen(str) - 1] = '\0';
		minishell(str);
		add_history(str);
	}
}

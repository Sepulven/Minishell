/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:52:09 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/28 15:48:47 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	g_exit_s = 0;

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

	(void)com;
	// TODO: Deve deixar alterar a string que recebemos até o a pos. que encontra-se válida.
	com = get_com_number(&str);
	str = expander(str);
	token_num = count_tokens_in_command(str);
	tokens = lexer(str, token_num);
	parser_list = parser(tokens, *env());
	if (!parser_list)
		return ;
	// print_parser(parser_list);
	if (parser_list)
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
	char	***tokens;
	int		com;

	str = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	(void)tokens;
	(void)com;
	(void)execute;
	com = 0;
	*env() = dup_env(envp);
	while (1)
	{
		ft_printf("myshell:> ");
		str = get_next_line(0);
		str[ft_strlen(str)] = '\0';
		minishell(str);
		get_next_line(-1);
	}
}

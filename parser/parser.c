/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:08:43 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/18 11:40:32 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parser.h"
#include "../minishell.h"

/*
	* Não é preciso dar free no command token, pois ja damos free fora do escopo.
	* Devemos sempre manter a integridade da função original
*/
char	*token_to_field(char *command_token)
{
	char	*field;

	if (0 && ft_strlen(command_token) == 2)
		return (ft_strdup(""));
	field = formatter(expander(ft_strdup(command_token)));
	ft_printf("%s\n", field);
	return (field);
}

/*
	* Adciona a matrix de param o novo parametro;
	* Não é preciso dar free do param.
*/
char	**add_param(char **matrix, char *param)
{
	char	**new_matrix;
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = ft_calloc(i + 2, sizeof (char *));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = token_to_field(param);
	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	if (matrix)
		free(matrix);
	return (new_matrix);
}

static void	delete_current_heredoc(int inf)
{
	char	*pathname;

	close(inf);
	pathname = take_current_pathname();
	unlink(pathname);
	free(pathname);
}

static void	treat_redirects(t_com_list *new, char *command_token)
{
	if (!ft_strncmp(command_token, "<<", 2))
	{
		if (new->inf)
			delete_current_heredoc(new->inf);
		new->inf = heredoc(command_token);
	}
	else if (!ft_strncmp(command_token, ">>", 2))
	{
		if (new->outf)
			close(new->outf);
		new->outf = append(command_token);
	}
	else if (!ft_strncmp(command_token, "<", 1))
	{
		if (new->inf)
			close(new->inf);
		new->inf = redirect_inf(command_token);
	}
	else if (!ft_strncmp(command_token, ">", 1))
	{
		if (new->outf)
			close(new->outf);
		new->outf = redirect_outf(command_token);
	}
}

/*
	* Receberemos uma matrix com os tokens do repesctivo comando e o path.
	
	* Percorro a matrix redefindo os inf e ouf, dependendo de cada situção.
*/
t_com_list	*get_node(char **command_token, char **paths)
{
	t_com_list	*new;
	int			i;

	new = malloc(sizeof(t_com_list));
	if (!new)
		return (NULL);
	initialize_lst(&new);
	i = 0;
	while (command_token[i] && (new->inf != -1 && new->outf != -1))
	{
		if (!new->command && !ft_isredirects(command_token[i]))
		{
			new->command = token_to_field(command_token[i]);
			new->path = check_path(paths, new->command);
			new->param = add_param(new->param, command_token[i]);
		}
		else if (!ft_isredirects(command_token[i]))
			new->param = add_param(new->param, command_token[i]);
		else if (ft_isredirects(command_token[i]))
			treat_redirects(new, command_token[i]);
		i++;
	}
	return (new);
}

/*
	* Recebe os tokens e as váriaveis de ambiente para popular o parse;
	* Como eu havia definido alteriormente iremos percorrer estes tokens para popular a matriz;

	* Tinhamos algums problemas com os free... Devo tomar cuidado pois temos uma função que dando
	* free conforme vai recebendo os parametros.
*/
t_com_list	*parser(char ***tokens, char **envp)
{
	t_com_list	*lst;
	t_com_list	*node;
	int			i;
	char		**paths;

	if (!tokens || !*tokens || !**tokens || !***tokens)
		return (NULL);
	paths = get_paths(envp);
	i = 0;
	lst = NULL;
	print_lexer(tokens);
	while (tokens[i])
	{
		node = get_node(tokens[i], paths);
		i++;
		if (!node)
			exit(EXIT_FAILURE);
		__ft_lstadd_back(&lst, node);
	}
	if (paths)
		free_double(paths);
	if (tokens)
		free_tokens(tokens);
	return (lst);
}

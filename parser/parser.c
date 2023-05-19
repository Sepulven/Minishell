/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:08:43 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:58:59 by asepulve         ###   ########.fr       */
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

static void	treat_redirects(char *command_token, t_memory mem)
{
	if (!ft_strncmp(command_token, "<<", 2))
	{
		if (mem.new->inf)
			delete_current_heredoc(mem.new->inf);
		mem.new->inf = heredoc(command_token, mem);
	}
	else if (!ft_strncmp(command_token, ">>", 2))
	{
		if (mem.new->outf)
			close(mem.new->outf);
		mem.new->outf = append(command_token);
	}
	else if (!ft_strncmp(command_token, "<", 1))
	{
		if (mem.new->inf)
			close(mem.new->inf);
		mem.new->inf = redirect_inf(command_token);
	}
	else if (!ft_strncmp(command_token, ">", 1))
	{
		if (mem.new->outf)
			close(mem.new->outf);
		mem.new->outf = redirect_outf(command_token);
	}
}

/*
	* Receberemos uma matrix com os tokens do repesctivo comando e o path.
	
	* Percorro a matrix redefindo os inf e ouf, dependendo de cada situção.
*/

t_com_list	*get_node(char **command_token, t_memory mem)
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
			new->path = check_path(mem.paths, new->command);
			new->param = add_param(new->param, command_token[i]);
		}
		else if (!ft_isredirects(command_token[i]))
			new->param = add_param(new->param, command_token[i]);
		else if (ft_isredirects(command_token[i]))
			treat_redirects(command_token[i], (t_memory){new, mem.lst, \
			NULL, mem.paths, mem.tokens});
		i++;
	}
	return (new);
}

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
	while (tokens[i])
	{
		node = get_node(tokens[i], (t_memory){0, lst, 0, paths, tokens});
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

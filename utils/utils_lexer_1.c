/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:13:41 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:05:29 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

/*
	* Verifica se é um redirect, caso seja retorna o tamanho do redirect.
	* Se não retorna 0.
*/
int	ft_isredirects(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	else if (!ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

/*
	* Recebe uma string que talvez possua um redirect.
	* Caso possua retorna o número total de casas para saltar
	* o redirect e o seu respectivo file.
*/
int	ft_jump_redirect_token(char *str)
{
	int	i;

	i = 0;
	i += jump_white_spaces(&str[i]);
	i += ft_isredirects(&str[i]);
	i += jump_white_spaces(&str[i]);
	while (str[i] && !ft_iswhitespace(str[i]) && !ft_isredirects(&str[i]))
	{
		if (str[i] == '\'' || str[i] == '\"')
			i += jump_quotes(&str[i]);
		else
			i++;
	}
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2, char *opt)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = (char)s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = (char)s2[j++];
	str[i] = '\0';
	if (ft_strncmp("s1s2", opt, 4) == 0)
	{
		free(s1);
		free(s2);
	}
	else if (ft_strncmp("s1", opt, 2) == 0)
		free(s1);
	else if (ft_strncmp("s2", opt, 2) == 0)
		free(s2);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:47:01 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 19:04:53 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	quotes_case(char **formatted, char *unformatted, \
				int str_size, int i)
{
	char	*str;

	str = ft_calloc((str_size - 2) + 1, sizeof (char));
	if (!str)
		return ;
	ft_strlcpy(str, &unformatted[i + 1], str_size - 1);
	*formatted = ft_strjoin_free(*formatted, str, "s1s2");
}

static void	str_out_quotes_case(char **formatted, char *unformatted, \
			int str_size, int i)
{
	char	*str;

	str = ft_calloc(str_size + 1, sizeof (char));
	if (!str)
		return ;
	ft_strlcpy(str, &unformatted[i], str_size + 1);
	*formatted = ft_strjoin_free(*formatted, str, "s1s2");
}

static char	*prepare_unformatted(char *unformatted, int *str_size, \
			int *i, char **formatted)
{
	char	*str;

	*str_size = 0;
	*i = 0;
	*formatted = ft_strdup("");
	if (!formatted)
		return (NULL);
	str = ft_strtrim(unformatted, " \n\t\f\r");
	if (!str)
	{
		free(unformatted);
		return (NULL);
	}
	free(unformatted);
	unformatted = ft_strdup(str);
	if (!unformatted)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (unformatted);
}

char	*_formatter(char *formatted, char *unformatted, int str_size)
{
	int	i;

	i = 0;
	while (unformatted && unformatted[i])
	{
		str_size = jump_quotes(&unformatted[i]);
		if (str_size)
			quotes_case(&formatted, unformatted, str_size, i);
		i = i + str_size;
		str_size = jump_str_out_quotes(&unformatted[i]);
		if (str_size)
			str_out_quotes_case(&formatted, unformatted, str_size, i);
		i = i + str_size;
		str_size = jump_white_spaces(&unformatted[i]);
		if (str_size)
			formatted = ft_strjoin_free(formatted, " ", "s1");
		i = i + str_size;
	}
	if (unformatted)
		free(unformatted);
	return (formatted);
}

char	*formatter(char *unformatted)
{
	char	*formatted;
	int		i;
	int		str_size;

	unformatted = prepare_unformatted(unformatted, &str_size, &i, &formatted);
	if (!unformatted)
	{
		free(formatted);
		return (ft_strdup(""));
	}
	return (_formatter(formatted, unformatted, str_size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:47:01 by asepulve          #+#    #+#             */
/*   Updated: 2023/04/27 00:28:48 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	* * Notas velhas, podem ser importantes no futuro.
	* Atenção os casos em que são syntax error já encontram-se validado.
	* Agora é apenas necessário popular até o ultimo este erro, apartir dele
	* nada mais importar.

	* Algo:
	* Percorremos a string até encontrar o |
	* Para percorremos a string precisamos saltar os quotes;
	* Também é necessario encontrar um caractere inválido, caso haja. E parar de imediato.
	* Quanto encontrarmos o |:
	* Retiraremos formataremos para retirar as aspas do começo do primeiro comando
	* Deixaremos tudo separado por apenas um espaço, retiraremos os whitespaces
	* Copiaremos este valor para dentro da nossa matrix;

*/

/*
	* Preciso refactorar para colocar em menos linhas;
	* Vamos dar trim dos seguintes caracteres: ( ,",',|)
*/
char	*formatter(char *unformatted)
{
	char	*formatted;
	char	*str;
	int		i;
	int		str_size;

	str_size = 0;
	i = 0;
	str = ft_strtrim(unformatted, " \n\t\f\r");
	free(unformatted);
	unformatted = ft_strdup(str);
	free(str);
	formatted = ft_strdup("");
	while (unformatted[i])
	{
		str_size = jump_quotes(&unformatted[i]);
		if (str_size) //  * Tenho sempre que levar em consideração o string size por conta das aspas.
		{
			str = ft_calloc((str_size - 2) + 1, sizeof (char));
			if (!str)
				return (NULL);
			ft_strlcpy(str, &unformatted[i + 1], str_size - 1);
			formatted = ft_strjoin_free(formatted, str, "s1s2");
		}
		i = i + str_size;
		str_size = jump_str_out_quotes(&unformatted[i]);
		if (str_size) // * Str out quotes case
		{
			str = ft_calloc(str_size + 1, sizeof (char));
			if (!str)
				return (NULL);
			ft_strlcpy(str, &unformatted[i], str_size + 1);
			formatted = ft_strjoin_free(formatted, str, "s1s2");
		}
		i = i + str_size;
		str_size = jump_white_spaces(&unformatted[i]);
		if (str_size) // * White space case 
			formatted = ft_strjoin_free(formatted, " ", "s1");
		i = i + str_size;
	}
	if (unformatted)
		free(unformatted);
	return (formatted);
}

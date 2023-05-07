/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:47:21 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/06 23:27:26 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./executor.h"
// #include "../important.h"

extern int	g_exit_s;

void	write_error(char *str, int status)
{
	ft_putendl_fd(str, 2);
	g_exit_s = status;
}

void	error_m(char *command, char *param, char *str, int s)
{
	ft_putendl_fd(command, 2);
	ft_putendl_fd(": ", 2);
	ft_putendl_fd(param, 2);
	ft_putendl_fd(": ", 2);
	ft_putendl_fd(str, 2);
	g_exit_s = s;
}

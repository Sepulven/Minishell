/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:18:11 by asepulve          #+#    #+#             */
/*   Updated: 2023/05/19 15:12:08 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	handler_quit(int signal)
{
	if (signal == SIGQUIT)
		write(2, "Quit (core dumped)\n", 20);
}

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGINT || signal == SIGQUIT)
		return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __def_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:32:01 by mvicente          #+#    #+#             */
/*   Updated: 2023/05/12 12:58:20 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

int	**pid(void)
{
	static int	*pid;

	return (&pid);
}

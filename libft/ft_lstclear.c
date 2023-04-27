/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:14:15 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/08 16:56:39 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*current;

	current = *lst;
	if (!current)
		return ;
	while (current)
	{
		temp = current->next;
		ft_lstdelone(current, del);
		current = temp;
	}
	*lst = NULL;
}

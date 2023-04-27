/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asepulve <asepulve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:12:40 by asepulve          #+#    #+#             */
/*   Updated: 2022/11/09 16:55:09 by asepulve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*newlist;

	if (!f || !lst || !del)
		return (NULL);
	newlist = NULL;
	while (lst)
	{
		newnode = ft_lstnew((*f)(lst->content));
		if (!newnode)
		{	
			ft_lstclear(&newlist, del);
			newlist = NULL;
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}

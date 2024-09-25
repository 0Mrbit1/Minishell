/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:22:57 by acharik           #+#    #+#             */
/*   Updated: 2023/11/24 17:43:48 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_node;
	t_list	*node;

	if (!lst || !f || !del)
		return (NULL);
	first_node = ft_lstnew(f(lst->content));
	if (!first_node)
		return (NULL);
	node = first_node;
	lst = lst->next;
	while (lst)
	{
		node->next = ft_lstnew(f(lst->content));
		if (!(node->next))
		{
			ft_lstclear(&first_node, del);
			return (NULL);
		}
		node = node->next ;
		ft_lstadd_back(&first_node, node);
		lst = lst->next;
	}
	node -> next = NULL;
	return (first_node);
}

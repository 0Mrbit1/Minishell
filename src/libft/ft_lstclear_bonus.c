/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:34:18 by acharik           #+#    #+#             */
/*   Updated: 2023/11/26 22:53:59 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*to_free;

	if (!lst || !del)
		return ;
	node = *lst;
	to_free = node;
	while (node)
	{
		del(node->content);
		to_free = node;
		node = node->next;
		free(to_free);
	}
	*lst = NULL;
}

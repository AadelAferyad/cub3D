/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:00:19 by aaferyad          #+#    #+#             */
/*   Updated: 2024/11/06 17:00:20 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*node;

	head = *lst;
	if (!lst || !(*lst) || !del)
		return ;
	while (head)
	{
		node = head;
		head = head->next;
		ft_lstdelone(node, del);
	}
	*lst = NULL;
}

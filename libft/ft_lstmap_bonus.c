/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:47:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/05 15:49:11 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*s;
	t_list	*list;

	list = NULL;
	while (lst)
	{
		s = ft_lstnew(f(lst->content));
		if (lst == NULL)
		{
			ft_lstclear (&list, del);
			return (0);
		}
		ft_lstadd_back (&list, s);
		lst = lst->next;
	}
	return (list);
}

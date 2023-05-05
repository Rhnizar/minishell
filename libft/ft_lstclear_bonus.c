/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:30:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/17 13:09:19 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		list = (*lst)->next;
		ft_lstdelone (*lst, del);
		*lst = list;
	}
}

// void del(void *content)
// {
// 	free(content);
// }

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew(ft_strdup("Hello"));
// 	t_list *no2;
// 		no2 = ft_lstnew(ft_strdup("Hello2"));
// 	no1->next = no2;

// 	ft_lstclear(&no1, del);
// 	while(no1)
// 	{
// 		printf("%s\n", no1->content);
// 		no1 = no1->next;
// 	}
// }
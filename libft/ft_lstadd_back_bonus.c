/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:07:18 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:54:02 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
			ft_lstlast (*lst)->next = new;
	}
}

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew("test1");

// 	t_list *no2;
// 		no2 = ft_lstnew("test2");
// 	ft_lstadd_back(&no1, no2);
// 	while(no1)
// 	{
// 		printf("%s\n", no1->content);
// 		no1 = no1->next;
// 	}
// }
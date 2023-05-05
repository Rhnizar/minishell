/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:56:01 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:52:39 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew("test1");

// 	t_list *no2;
// 		no2 = ft_lstnew("test454");
// 	no1->next = no2;

// 	t_list *test;
// 		test = ft_lstlast(no1);
// 	printf("%s", test->content);	
// }
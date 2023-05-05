/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:42:49 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 23:02:32 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void	f(void *r)
// {
// 	char *s = ft_strdup(r);
// 	s = "Where is this";
// 	printf("%s\n", s);
// }

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew("Hi");
// 	t_list *no2;
// 		no2 = ft_lstnew("Friend");

// 	no1->next = no2;

// 	ft_lstiter(no1 , f);

// }
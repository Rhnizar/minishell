/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:41:39 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:51:16 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew("test1");

// 	t_list *no2;
// 		no2 = ft_lstnew("test2");
// 	ft_lstadd_front(&no1, no2);
// 	while(no1)
// 	{
// 		printf("%s\n", no1->content);
// 		no1 = no1->next;
// 	}
// }
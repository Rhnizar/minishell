/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:50:48 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:52:15 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew("test1");

// 	t_list *no2;
// 		no2 = ft_lstnew("test2");
// 	no1->next = no2;
// 	printf("%d\n", ft_lstsize(no1));
// }

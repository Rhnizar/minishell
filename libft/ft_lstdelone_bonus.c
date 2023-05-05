/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:21:44 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:56:13 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del (lst->content);
	free (lst);
}

// void del(void *content)
// {
// 	free(content);
// }

// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew(ft_strdup("test1"));

// 	t_list *no2;
// 		no2 = ft_lstnew(ft_strdup("test2"));	 
// 	no1->next = no2;
// 	ft_lstdelone(no1, del);
// 	while(no1)
// 	{
// 		printf("%s\n", no1->content);
// 		no1 = no1->next;
// 	}
// }
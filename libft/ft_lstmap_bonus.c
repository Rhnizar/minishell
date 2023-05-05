/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:47:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/16 21:32:02 by rrhnizar         ###   ########.fr       */
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

// void	*f(void *cont)
// {
// 	char *str;
// 	str = ft_strdup(cont);
// 	str[0] = 'R';
// 	str[4] = 'R';
// 	return (str);
// }
// void	del1(void *contdel)
// {
// 	free(contdel);
// }
// int main(void)
// {
// 	t_list *no1;
// 		no1 = ft_lstnew(ft_strdup("test1"));
// 	t_list *no2;
// 		no2 = ft_lstnew(ft_strdup("test2"));

// 	no1->next = no2;

// 	t_list *test;
// 	test =  ft_lstmap(no1, f, del1);
// 	printf("==== After =====\n");
// 	while(no1)
// 	{
// 		printf("%s\n", test->content);
// 		no1 = no1->next;
// 	}
// }
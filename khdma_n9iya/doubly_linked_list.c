/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:45:58 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/08 07:56:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_lst
{
	int				n;
	struct s_lst	*next;
	struct s_lst	*prev;
}				t_lst;

void	create_list(t_lst **lst, int n)
{
	t_lst	*new;
	t_lst	*tmp;

	new = malloc(sizeof(t_lst));
	if (!new)
		return ;
	new->n = n;
	new->next = NULL;
	new->prev = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int main(void)
{
	t_lst	*lst;

	lst = NULL;
	int	n = 1;
	while (n != 4)
		create_list(&lst, n++);
	while (lst->next)
	{
		printf("%d\n", lst->n);
		lst = lst->next;
	}
	printf("%d\n", lst->n);
	printf("\n ------------ \n");
	while (lst->prev)
	{
		printf("%d\n", lst->n);
		lst = lst->prev;
	}
	printf("%d\n", lst->n);
	return (0);
}
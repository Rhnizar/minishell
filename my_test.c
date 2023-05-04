/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:51:57 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/04 08:20:03 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_list(t_list **list, t_cmdshell *cmdshell)
{
	t_list	*new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->cmdshell = cmdshell;
	new->next = NULL;
	*list = new;
}

int main(void)
{
	t_list	*lst;
	t_cmdshell	*shell1;

	shell1 = malloc(sizeof(t_cmdshell));
	lst = malloc(sizeof(t_list));
	lst->cmdshell = shell1;
	lst->next = NULL;
	
	printf("====>%d\n", lst->cmdshell->pip);
	// printf("====>%d", lst->next->cmdshell->pip);

	return (0);
}
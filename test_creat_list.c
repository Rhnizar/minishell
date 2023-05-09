/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_creat_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:23:17 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 17:26:40 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	// printf("me\n");
	t_tokens	*list;
	list = NULL;
	create_tokens(&list, "hello", 0);
	create_tokens(&list, "Rida", 0);
	create_tokens(&list, "Rhnizar", 0);

	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
	
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/19 16:09:12 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*read_line;
	t_tokens	*lst;

	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line)
		{
			if (read_line[0] != 0)
				add_history(read_line);
			lst = split_and_fill_list(read_line);
			while(lst)
			{
				printf("%s\n", lst->str);
				lst = lst->next;
			}
		}
		else
			break ;
	}
	printf("exit\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/20 11:31:13 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*read_line;
	t_tokens	*lst;
	// t_tokens	*tmp;

	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line)
		{
			if (read_line[0] != 0)
				add_history(read_line);
			lst = split_and_fill_list(read_line);
			printf("%d\n", syntax_error_handler(lst));
			// exit(1);
			// printf("%d\n", count_tokens(lst));
			// tmp = lst;
			// while(tmp)
			// {
			// 	printf("[%s]\n", tmp->str);
			// 	tmp = tmp->next;
			// }
		}
		else
			break ;
	}
	printf("exit\n");
	return (0);
}
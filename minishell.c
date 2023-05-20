/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/20 17:43:57 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*read_line;
	t_tokens	*tokens;
	t_cmdshell *lst_cmd;

	lst_cmd = NULL;
	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line)
		{
			if (read_line[0] != 0)
				add_history(read_line);
			tokens = split_and_fill_list(read_line);
			lst_cmd = fill_list_cmds(lst_cmd, tokens);
			// printf("%s\n", lst_cmd->cmds->cmd);
			while (lst_cmd)
			{
				printf("%s\n", lst_cmd->cmds->cmd);
				lst_cmd = lst_cmd->next;
			}
			// while(lst)
			// {
			// 	printf("%s\n", lst->str);
			// 	lst = lst->next;
			// }
		}
		else
			break ;
	}
	printf("exit\n");
	return (0);
}

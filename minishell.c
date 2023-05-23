/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/23 20:34:25 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char		*line;
	t_global	*global;

	while (1)
	{
		line = readline("minishell ~ ");
		if (line)
		{
			if (line[0] != 0)
				add_history(line);
			else
				continue ;
			if (fill_global_struct(&global, line, env) == -1)
				return (-1);
			printf("\n--------------------------------------------------------------------------\n");
			while (global->all_commands)
			{
				printf("cmd ==> %s\n", global->all_commands->cmds->cmd);
				printf("subshell ===> %s\n", global->all_commands->cmds->subshell);
				printf("operator ===> %d\n", global->all_commands->cmds->operator);
				printf("\n=======  all arguments  =======\n");
				while(global->all_commands->cmds->args)
				{
					printf("arg : %s\n", global->all_commands->cmds->args->str);
					global->all_commands->cmds->args = global->all_commands->cmds->args->next;
				}
				printf("\n======= all redirections =======\n");
				while(global->all_commands->cmds->redis)
				{
					printf("red : %s\n", global->all_commands->cmds->redis->str);
					printf("type red : %d\n", global->all_commands->cmds->redis->type);
					printf("-----------------------------\n");
					global->all_commands->cmds->redis = global->all_commands->cmds->redis->next;
				}
				global->all_commands = global->all_commands->next;
				printf("\n---------------------------------END CMD-----------------------------------------\n");
			}
		}
		else
			break ;
	}
	printf("exit\n");
	return (0);
}

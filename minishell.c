/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/28 14:08:43 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CTRL + C ===> SIGINT
// CTRL + D ===> EOF and SIGQUIT
// CTRL + \ ===> SIGQUIT


void	sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		rl_redisplay();
}


int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char		*line;
	t_global	*global;

	signal(SIGINT, sig_handl);
	signal(SIGQUIT, sig_handl);
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
				continue ;
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
			break;
	}
	printf("exit\n");
	return (0);
}

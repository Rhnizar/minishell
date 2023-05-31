/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 19:50:05 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f(void)
{
	struct termios	ter;

	tcgetattr(0, &ter);
	ter.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &ter);
}

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
	char		*line;
	t_global	*global;
	t_cmdshell	*commands;
	// t_args		*tmp_args;
	// t_redis		*tmp_redis;

	signal(SIGINT, sig_handl);
	signal(SIGQUIT, sig_handl);
	f();
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
			commands = global->all_commands;
			printf("\n--------------------------------------------------------------------------\n");
			while (global->env)
			{
				printf("%s=%s\n", global->env->var, global->env->value);
				global->env = global->env->next;
			}
			
			// while (commands)
			// {
			// 	tmp_args = commands->cmds->args;
			// 	tmp_redis = commands->cmds->redis;
			// 	if (tmp_args)
			// 		printf("cmd ==> %s\n", tmp_args->str);
			// 	else
			// 		printf("cmd ==> (null)\n");
			// 	printf("subshell ===> %s\n", commands->cmds->subshell);
			// 	printf("operator ===> %d\n", commands->cmds->operator);
			// 	printf("\n=======  all arguments  =======\n");
			// 	while(tmp_args)
			// 	{
			// 		printf("arg : %s\n", tmp_args->str);
			// 		tmp_args = tmp_args->next;
			// 	}
			// 	printf("\n======= all redirections =======\n");
			// 	while(tmp_redis)
			// 	{
			// 		printf("red : %s\n", tmp_redis->str);
			// 		printf("type red : %d\n", tmp_redis->type);
			// 		printf("-----------------------------\n");
			// 		tmp_redis = tmp_redis->next;
			// 	}
			// 	commands = commands->next;
			// 	printf("\n---------------------------------END CMD-----------------------------------------\n");
			// }
			all_free_parsing(global);
		}
		else
		{
			free(line);
			break ;
		}
	}
	printf("exit\n");
	return (0);
}

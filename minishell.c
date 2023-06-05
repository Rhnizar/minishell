/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/05 16:12:20 by rrhnizar         ###   ########.fr       */
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

int	r;
void	sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		if (r == 0)
			write(1, "\n", 1);
		// printf("\n");
		rl_catch_signals = 0;
		close(0);
		r = 1;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char		*line;
	t_global	*global;
	t_args		*args;
	int			fd;
	// t_redis		*redis;

	signal(SIGINT, sig_handl);
	signal(SIGQUIT, SIG_IGN);
	f();
	init_global(&global, env);
	fd = dup(0);
	r = 0;
	while (1)
	{
		dup2(fd, 0);
		rl_catch_signals = 1;
		line = readline("minishell ~ ");
		if (line)
		{
			if (line[0] != 0)
				add_history(line);
			else
				continue ;
			if (fill_global_struct(&global, line) == -1)
				continue ;
			global->all_commands->cmds->args = args_expander(global);
			args = global->all_commands->cmds->args;
			// printf("----------------\n");
			// while(args)
			// {
			// 	printf("%s\n", args->str);
			// 	args = args->next;
			// }
			// redis = global->all_commands->cmds->redis;
			// while (redis)
			// {
			// 	printf("redis: %s\n", redis->str);
			// 	printf("type: %d\n", redis->type);
			// 	redis = redis->next;
			// }
			if (ft_strncmp("export", line, ft_strlen("export")) == 0)
				add_to_export_or_print(global->env, global->export, args);
			if (ft_strncmp("env", line, ft_strlen("env")) == 0)
				print_env(global->env);
			if (ft_strncmp("unset", line, ft_strlen("unset")) == 0)
				unset(&global->env, &global->export, args);
			// while(args)
			// {
			// 	printf("%s\n", args->str);
			// 	args = args->next;
			// }
			free_commands(global->all_commands);
			free(line);
		}
		else
		{
			if (rl_catch_signals == 0)
				continue ;
			else
				break ;
		}
	}
	global_free(global);
	printf("exit\n");
	return (0);
}

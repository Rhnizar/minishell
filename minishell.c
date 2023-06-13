/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/13 22:52:35 by rrhnizar         ###   ########.fr       */
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
/* rl_getc_function  what is ??*/

int	g_r;

void	sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		if (g_r == 0)
			write(1, "\n", 1);
		rl_catch_signals = 0;
		close(0);
		g_r += 1;
	}
}

// void builtins(t_global *global, char *line)
// {
// 	if (ft_strncmp("export", line, ft_strlen("export")) == 0)
// 		add_to_export_or_print(global->env, global->export, global->all_commands->cmds->args);
// 	if (ft_strncmp("env", line, ft_strlen("env")) == 0)
// 		print_env(global->env);
// 	if (ft_strncmp("unset", line, ft_strlen("unset")) == 0)
// 		unset(&global->env, &global->export, global->all_commands->cmds->args);
// 	if (ft_strncmp("exit", line, ft_strlen("exit")) == 0)
// 		exitt(global->all_commands->cmds->args);
// 	if (ft_strncmp("pwd", line, ft_strlen("pwd")) == 0)
// 		pwd(global);
// 	if (ft_strncmp("cd", line, ft_strlen("cd")) == 0)
// 		cd(global, global->all_commands->cmds->args, global->export);
// 	if (ft_strncmp("echo", line, ft_strlen("echo")) == 0)
// 		echo(global->all_commands->cmds->args);
// }

// void builtins(t_global **global, char *line)
// {
// 	if (ft_strncmp("export", line, ft_strlen("export")) == 0)
// 		add_to_export_or_print((*global)->env, (*global)->export, (*global)->all_commands->cmds->args);
// 	if (ft_strncmp("env", line, ft_strlen("env")) == 0)
// 		print_env((*global)->env);
// 	if (ft_strncmp("unset", line, ft_strlen("unset")) == 0)
// 		unset(&(*global)->env, &(*global)->export, (*global)->all_commands->cmds->args);
// 	if (ft_strncmp("exit", line, ft_strlen("exit")) == 0)
// 		exitt((*global)->all_commands->cmds->args);
// 	if (ft_strncmp("pwd", line, ft_strlen("pwd")) == 0)
// 		pwd(*global);
// 	if (ft_strncmp("cd", line, ft_strlen("cd")) == 0)
// 		cd(*global, (*global)->all_commands->cmds->args, (*global)->export);
// 	if (ft_strncmp("echo", line, ft_strlen("echo")) == 0)
// 		echo((*global)->all_commands->cmds->args);
// 	printf("[%d]\n", (*global)->exit_status);
// }

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char		*line;
	t_global	*global;
	int			tmp_gr;
	// t_args		*args;
	int			fd;
	// t_redis		*redis;

	signal(SIGINT, sig_handl);
	signal(SIGQUIT, SIG_IGN);
	f();
	init_global(&global, env);
	fd = dup(0);
	g_r = 0;
	tmp_gr = 0;
	while (1)
	{
		dup2(fd, 0);
		rl_catch_signals = 1;
		if (g_r != tmp_gr)
			global->exit_status = 1;
		tmp_gr = g_r;
		line = readline("minishell ~ ");
		if (line)
		{
			if (line[0] != 0)
				add_history(line);
			else
				continue ;
			if (fill_global_struct(&global, line, 1) == -1)
				continue ;
			// if (fill_global_struct(&global, line) == -1)
			// 	continue ;
			execution(global);
			// redis = redis_expander(global->all_commands->cmds->redis, global->env, 0);
			// while (redis)
			// {
			// 	printf("value: [%s]\ttype: [%d]\n", redis->str, redis->type);
			// 	redis = redis->next;
			// }
			// global->all_commands->cmds->args = args_expander(global);
			// args = global->all_commands->cmds->args;
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
			// builtins(global, line);
			// printf("-------------------\n");
			// while(args)
			// {
			// 	printf("%s\n", args->str);
			// 	args = args->next;
			// }

			// printf("\n--------------------------------------------------------------------------\n");
			// while (global->all_commands)
			// {
			// 	// printf("cmd ==> %s\n", global->all_commands->cmds->cmd);
			// 	printf("subshell ===> %s\n", global->all_commands->cmds->subshell);
			// 	printf("operator ===> %d\n", global->all_commands->cmds->operator);
			// 	printf("\n=======  all arguments  =======\n");
			// 	while(global->all_commands->cmds->args)
			// 	{
			// 		printf("arg : %s\n", global->all_commands->cmds->args->str);
			// 		global->all_commands->cmds->args = global->all_commands->cmds->args->next;
			// 	}
			// 	printf("\n======= all redirections =======\n");
			// 	while(global->all_commands->cmds->redis)
			// 	{
			// 		printf("red : %s\n", global->all_commands->cmds->redis->str);
			// 		printf("type red : %d\n", global->all_commands->cmds->redis->type);
			// 		printf("-----------------------------\n");
			// 		global->all_commands->cmds->redis = global->all_commands->cmds->redis->next;
			// 	}
			// 	global->all_commands = global->all_commands->next;
			// 	printf("\n---------------------------------END CMD-----------------------------------------\n");
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

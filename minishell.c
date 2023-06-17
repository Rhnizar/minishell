/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/17 01:43:14 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_ter(void)
{
	struct termios	ter;

	tcgetattr(0, &ter);
	ter.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &ter);
}

int	g_r;
void	sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		if (g_r == 0)
			write(1, "\n", 1);
		// rl_catch_signals = 0;
		close(0);
		g_r += 1;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	char		*line;
	t_global	*global;
	int			tmp_gr;
	int			fd;
	int			final_exit;

	signal(SIGINT, sig_handl);
	signal(SIGQUIT, SIG_IGN);
	ctl_ter();
	init_global(&global, env);
	fd = dup(0);
	g_r = 0;
	tmp_gr = 0;
	while (1)
	{
		dup2(fd, 0);
		// rl_catch_signals = 1;
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
			if (fill_global_struct(&global, line) == -1)
				continue ;
			execution(global);
			free_commands(global->all_commands);
			free(line);
		}
		else
		{
			// if (rl_catch_signals == 0)
			// 	continue ;
			// else
				break ;
		}
	}
	final_exit = global->exit_status;
	global_free(global);
	// printf("exit\n");
	return (final_exit);
}

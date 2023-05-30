/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:59:24 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/30 10:58:24 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

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

int stop_her = 0;
void	sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		rl_catch_signals = 0;
		stop_her = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		rl_redisplay();
}

void	herdoc(char *delimiter)
{
	char	*line;

	stop_her = 0;
	while (1)
	{
		if (rl_catch_signals == 0)
			break ;
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		free(line);
	}
}

int main(void)
{
	char	*line;
	f();
	signal(SIGINT, sig_handl);
	signal(SIGQUIT, sig_handl);
	while(1)
	{
		line = readline("--> ");
		if (line)
		{
			if (line[0] != 0)
				add_history(line);
			// if (line[0] == '<')
			// 	herdoc("eof");
		}
		else
			break;
	}
	printf("exit\n");
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:46:02 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 11:49:42 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_echo(void)
{
	struct termios ter;

	tcgetattr(0, &ter);
	ter.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &ter);
}

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

void	herdoc(char *del)
{
	char *line;

	while(1)
	{
		line = readline("herdoc> ");
		if (line)
		{
			if (ft_strncmp(del, line, ft_strlen(del)) == 0)
				break;
		}
		else
			break;
	}
}

int main(void)
{
	char	*line;

	ctl_echo();
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
			if (ft_strncmp("<<", line, 2) == 0)
				herdoc("eof");
		}
		else
			break;
	}
	printf("exit\n");
	return (0);
}
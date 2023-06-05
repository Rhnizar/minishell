/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:46:02 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/05 15:45:42 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ctl_echo(void)
// {
// 	struct termios ter;

// 	tcgetattr(0, &ter);
// 	ter.c_lflag &= ~ECHOCTL;
// 	tcsetattr(0, 0, &ter);
// }

// int	fd = 0;
// void	sig_handl(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		fd=dup(0);
// 		close(0);
// 		rl_catch_signals = 0;
// 	}
// }

// void	herdoc(char *del)
// {
// 	char *linee;

// 	while(1)
// 	{
// 		linee = readline("herdoc> ");
// 		if (linee)
// 		{
// 			if (ft_strncmp(del, linee, ft_strlen(del)) == 0)
// 				break;
// 		}
// 		else
// 			break;
// 	}
// }

int main(void)
{
	char	*line;

	// ctl_echo();
	// signal(SIGINT, sig_handl);
	// signal(SIGQUIT, SIG_IGN);
	// while (1)
	// {
	// 	if (fd > 0)
	// 		dup2(fd, 0);
	// 	rl_catch_signals = 1;
	// 	line = readline("minishell ~ ");
	// 	if (line)
	// 	{
	// 		if (line[0] != 0)
	// 			add_history(line);
	// 		else
	// 			continue ;
	// 		if (ft_strncmp("<<", line, 2) == 0)
	// 			herdoc("eof");
	// 	}
	// 	else
	// 	{
	// 		if (rl_catch_signals == 0)
	// 			continue ;
	// 		else
	// 			break;
	// 	}
	// }
	t_tokens *tmp1;
	t_tokens *tmp2;
	t_tokens *tmp3;

	if (tmp3 == NULL)
		printf("yes\n");
	else
		printf("no\n");
	return (0);
}

// int main(void)
// {
// 	printf("%zu\n", ft_strlen("He\x07llo"));
// 	return (0);
// }

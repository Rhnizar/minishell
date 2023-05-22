/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:46:02 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/22 18:07:40 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// typedef enum e_redirtypes
// {
// 	HEREDOC,
// 	FILE_IN,
// 	FILE_OUT,
// 	FILE_APPEND
// } t_rtype;

int main()
{
	printf("%d\n", FILE_APPEND);
	printf("%d\n", HEREDOC);
	printf("%d\n", FILE_IN);
	printf("%d\n", FILE_OUT);
	// pid_t  pid;

	// int i = 0;
	// while (++i < 4)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		printf("child\n");
	// 		// while (1);
	// 	}
	// 		// break ;
	// }
	// if (pid == 0)
	// {
	// 	while (1);
	// }
	// waitpid(-1, NULL, 0);
	// char **str = ft_calloc(3, sizeof(char *));

	// printf("%s\n", str[0]);
	// printf("%s\n", str[1]);
	// printf("%s\n", str[2]);


	// char *arg[] = {"ls", "( ls )", NULL};
	// int fd = open("Makefile", O_RDONLY);

	// dup2(fd, 0);


	// dup2();
	// execve("/bin/ls", arg, NULL);

	return (0);
}
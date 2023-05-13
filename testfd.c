/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:56:33 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/12 20:00:44 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
		while (s[i])
			write(fd, &s[i++], 1);
}

int main()
{
	// int fd = open("test.txt", O_CREAT|O_RDWR, 0777);
	// close(fd);
	// pid_t pid[10];

	// int i = -1;
	// while (++i < 10)
	// {
	// 	pid[i] = fork();
	// 	if (pid[i] == 0)
	// 	{
	// 		if (close(fd) == -1)
	// 			printf("Error from child of close\n");
	// 	}
	// }
	// i = -1;
	// while (++i < 10)
	// 	waitpid(pid[i], 0, 0);
	// unlink ("test.txt");
	// char *args[] = {"/bin/echo", "\"test test\"", NULL};
	// execve("/bin/echo", args, NULL);
	return (0);
}

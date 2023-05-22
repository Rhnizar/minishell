/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:56:33 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 23:17:03 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mandatory/minishell.h"

static void	write_to_pipe(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	free(line);
}

void	here_doc(char *delimiter)
{

	// pid = fork();
	// if (pid == 0)
	// {
	
	// 	close (fd);
	// 	exit(0);
	// }
	// close (fd[1]) == -1;

}


// int main()
// {
// 	int	fd1 = open("/tmp/.tmp", O_CREAT|O_RDWR, 0777);
// 	int fd2 = open("outfile", O_CREAT|O_RDWR|O_TRUNC, 0777);
// 	write_to_pipe(fd1, "eof");
// 	close(fd1);
// 	fd1 = open("/tmp/.tmp", O_CREAT|O_RDWR, 0777);
// 	dup2(fd1, STDIN_FILENO);
// 	close(fd1);

// 	dup2(fd2, STDOUT_FILENO);
// 	close(fd2);
// 	char *args[] = {"/bin/cat", "-e", NULL};
// 	unlink(".tmp");
// 	execve("/bin/cat", args, NULL);
// 	return (0);
// }

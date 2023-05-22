/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:27 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 22:29:09 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

static void	write_to_pipe(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
}

void	here_doc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		print_error(NULL, NULL, 1);
	pid = fork();
	if (pid == -1)
		print_error(NULL, NULL, 1);
	if (pid == 0)
	{
		close (fd[0]);
		write_to_pipe(fd[1], delimiter);
		close (fd[1]);
		exit(0);
	}
	if (close (fd[1]) == -1 || dup2(fd[0], STDIN_FILENO) == -1 || \
	close (fd[0]) == -1)
		print_error(NULL, NULL, 1);
	waitpid(pid, NULL, 0);
}


/*here doc using file*/

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
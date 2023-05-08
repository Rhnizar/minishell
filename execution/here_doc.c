/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:27 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/08 13:30:40 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_to_pipe(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
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

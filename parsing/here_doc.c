/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:35:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/14 17:01:48 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	here_doc(char *delimiter)
{
	char	*line;
	int		fd[2];
	int		read_fd;

	if (pipe(fd) == -1)
		return (print_error(NULL, NULL, -1), -1);
	read_fd = dup(fd[0]);
	if (close (fd[0]) == -1)
		return (print_error(NULL, NULL, -1), -1);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	free(line);
	if (close (fd[1]) == -1)
		return (print_error(NULL, NULL, -1), -1);
	return (read_fd);
}

static int	get_last_heredoc(t_redis *redis)
{
	t_redis	*tmp;
	int		fd_new;
	int		fd_prev;

	fd_new = -2;
	fd_prev = -1;
	tmp = redis;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (fd_prev != -1 && close (fd_prev) == -1)
				return (print_error(NULL, NULL, -1), -1);
			fd_new = here_doc(tmp->str);
			fd_prev = fd_new;
			if (fd_new == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (fd_new);
}

void	run_heredocs(t_global *global)
{
	t_cmdshell	*tmp;

	tmp = global->all_commands;
	while (tmp)
	{
		tmp->cmds->fd_herdoc = get_last_heredoc(tmp->cmds->redis);
		tmp = tmp->next;
	}
}

int	close_herdocs(t_cmdshell *commands, int stop)
{
	t_cmdshell	*tmp;
	int			i;

	i = 0;
	tmp = commands;
	while (tmp && i < stop)
	{
		if (tmp->cmds->fd_herdoc != -2 && close (tmp->cmds->fd_herdoc) == -1)
			return (1);
		i++;
		tmp = tmp->next;
	}
	return (0);
}

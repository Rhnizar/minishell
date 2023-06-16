/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:41:16 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/16 11:08:14 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	_open_redis(t_global *global, t_redis *tmp, \
int *fd_read, int *fd_write)
{
	t_redis	*new_redi;

	new_redi = NULL;
	new_redi = redis_expander(global, tmp);
	if (tmp && new_redi == NULL)
		return (-1);
	if (tmp->type == FILE_IN)
	{
		if (*fd_read != -1)
			close (*fd_read);
		(*fd_read) = input_redirection(new_redi->str);
		if ((*fd_read) == -1)
			return (-1);
	}
	if (tmp->type == FILE_OUT || tmp->type == FILE_APPEND)
	{
		if (*fd_write != -1)
			close (*fd_write);
		if (tmp->type == FILE_OUT)
			(*fd_write) = output_redirection(new_redi->str);
		else if (tmp->type == FILE_APPEND)
			(*fd_write) = append_output(new_redi->str);
		if ((*fd_write) == -1)
			return (-1);
	}
	free_redis(new_redi);
	return (0);
}

int	open_redis(t_global *global, t_redis *redis, int *fd_read, int *fd_write)
{
	t_redis	*tmp;
	int		last;

	tmp = redis;
	last = 0;
	while (tmp)
	{	
		if (tmp->type != HEREDOC)
		{
			last = 0;
			if (_open_redis(global, tmp, fd_read, fd_write))
				return (-1);
		}
		else if (tmp->type == HEREDOC)
			last = 1;
		tmp = tmp->next;
	}
	if (last == 1)
	{
		if (*fd_read != -1)
			close (*fd_read);
		*fd_read = -1;
	}
	return (0);
}

int	manage_redirection(t_global *global, t_redis *redis)
{
	int	fd_read;
	int	fd_write;

	fd_read = -1;
	fd_write = -1;
	if (open_redis(global, redis, &fd_read, &fd_write))
		return (1);
	if (fd_read != -1 && dup2(fd_read, STDIN_FILENO) == -1)
		return (print_error(NULL, NULL, -1), 1);
	if (fd_write != -1 && dup2(fd_write, STDOUT_FILENO) == -1)
		return (print_error(NULL, NULL, -1), 1);
	return (0);
}

int	manage_redirection_builtins(t_global *global, t_cmdshell *cmd)
{
	int	fd_read;
	int	fd_write;
	int	fd_tmp;

	fd_read = -2;
	fd_write = -2;
	fd_tmp = -1;
	if (cmd->cmds->fd_herdoc != -2)
		close (cmd->cmds->fd_herdoc);
	if (open_redis(global, cmd->cmds->redis, &fd_read, &fd_write))
		return (-2);
	if (fd_read != -1)
		close (fd_read);
	if (fd_write != -1)
	{
		fd_tmp = dup(1);
		dup2(fd_write, 1);
	}
	if (fd_write != -1)
		close (fd_write);
	return (fd_tmp);
}

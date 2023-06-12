/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:41:16 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/12 21:09:22 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_heredocs(t_redis *redis, int *need_expand)
{
	t_redis	*tmp;
	int		fd;

	fd = -2;
	(void)need_expand;
	tmp = redis;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			fd = here_doc(tmp->str);
			if (fd == 
			-1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (fd);
}

static int	_open_redis(t_global *global, t_redis *tmp, int *fd_read, int *fd_write)
{
	t_redis	*new_redi;

	new_redi = NULL;
	new_redi = redis_expander(global, tmp);
	if (tmp->type == FILE_IN)
	{
		close ((*fd_read));
		(*fd_read) = input_redirection(new_redi->str);
		if ((*fd_read) == -1)
			return (-1);
	}
	if (tmp->type == FILE_OUT || tmp->type == FILE_APPEND)
	{
		close ((*fd_write));
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

static int	open_redis(t_global *global, t_redis *redis)
{
	t_redis	*tmp;
	int		fd_read;
	int		fd_write;

	tmp = redis;
	fd_read = -1;
	fd_write = -1;
	while (tmp)
	{	
		if (tmp->type != HEREDOC)
		{
			if (_open_redis(global, tmp, &fd_read, &fd_write))
				return (1);
		}
		tmp = tmp->next;
	}
	if (fd_read != -1 && dup2(fd_read, STDIN_FILENO) == -1)
		return (print_error(NULL, NULL, -1), 1);
	if (fd_write != -1 && dup2(fd_write, STDOUT_FILENO) == -1)
		return (print_error(NULL, NULL, -1), 1);
	return (0);
}

int	manage_redirection(t_global *global, t_redis *redis)
{
	int	fd_herdoc;
	int	fd_redis;
	int	need_expantion;

	need_expantion = 0;
	fd_herdoc = open_heredocs(redis, &need_expantion);
	if (fd_herdoc != -2)
	{
		if (fd_herdoc == -1)
			exit(1);
		if (dup2(fd_herdoc, STDIN_FILENO) == -1)
			return (print_error(NULL, NULL, -1), 1);
	}
	fd_redis = open_redis(global, redis);
	if (fd_redis == -1)
		exit(1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_redis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:18:15 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/09 20:25:15 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	manage_redirection(t_global *global, t_redis *redis)
{
	int	fd_read;
	int	fd_write;

	fd_read = read_from_file(global, redis);
	if (fd_read != -2)
	{
		if (fd_read == -1)
			return (1);
		if (dup2(fd_read, STDIN_FILENO) == -1)
			return (print_error(NULL, NULL, -1), 1);
	}
	fd_write = write_to_file(global, redis);
	if (fd_write != -2)
	{
		if (fd_write == -1)
			return (1);
		if (dup2(fd_write, STDOUT_FILENO) == -1)
			return (print_error(NULL, NULL, -1), 1);
	}
	return (0);
}

int	open_heredoc(t_redis *redis, int *need_expand, int *last_heredoc)
{
	t_redis	*tmp;
	int		fd;
	int		i;

	fd = -2;
	i = 0;
	//to add later
	(void)need_expand;
	tmp = redis;
	while (tmp)
	{
		unlink ("/tmp/here_doc.txt");
		if (tmp->type == HEREDOC)
		{
			(*last_heredoc) = i;
			fd = here_doc(redis->str);
			if (fd == -1)
				return (-1);
		}
		i++;
		tmp = tmp->next;
	}
	return (fd);
}

int	open_infiles(t_global *global, t_redis *redis, int *last_heredoc)
{
	t_redis	*tmp;
	t_redis	*new_redi;
	int		fd;
	int		i;

	tmp = redis;
	fd = -2;
	i = 0;
	while (tmp)
	{
		close (fd);
		if (tmp->type == FILE_IN)
		{
			*last_heredoc = i;
			new_redi = redis_expander(global, redis);
			fd = input_redirection(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);
		}
		i++;
		tmp = tmp->next;
	}
	return (fd);
}

int	read_from_file(t_global *global, t_redis *redis)
{
	int	fd1;
	int	fd2;
	int	last1;
	int	last2;
	int	need_expand;

	fd1 = open_heredoc(redis, &need_expand, &last1);
	if (fd1 < 0)
		return (fd1);
	fd2 = open_infiles(global, redis, &last2);
	if (fd2 < 0)
		return (fd2);
	if (last1 > last2)
		return (fd1);
	return (fd2);
}

int	write_to_file(t_global *global, t_redis *redis)
{
	t_redis	*tmp;
	t_redis	*new_redi;
	int		fd;

	tmp = redis;
	fd = -2;
	while (tmp)
	{
		close (fd);
		if (tmp->type == FILE_APPEND)
		{
			new_redi = redis_expander(global, redis);
			fd = append_output(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);
		}
		else if (tmp->type == FILE_OUT)
		{
			new_redi = redis_expander(global, redis);
			fd = output_redirection(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);	
		}
		tmp = tmp->next;
	}
	return (fd);
}
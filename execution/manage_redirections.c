/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:41:16 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/11 11:28:49 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_heredocs(t_redis *redis, int *need_expand, int *last_heredoc)
{
	t_redis	*tmp;
	int		fd;
	int		i;

	fd = -2;
	i = 0;
	(void)need_expand;
	tmp = redis;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			(*last_heredoc) = i;
			fd = here_doc(tmp->str);
			if (fd == -1)
				return (-1);
		}
		i++;
		tmp = tmp->next;
	}
	return (fd);
}

static int	open_infiles(t_global *global, t_redis *redis, int *last_file)
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
		if (tmp->type == FILE_IN)
		{
			close (fd);
			*last_file = i;
			new_redi = redis_expander(global, tmp);
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

static int	read_from_file(t_global *global, t_redis *redis)
{
	int	need_expand;
	int	last1;
	int	last2;
	int	fd1;
	int	fd2;

	last1 = 0;
	last2 = 0;
	fd1 = open_heredocs(redis, &need_expand, &last1);
	if (fd1 == -1)
		return (fd1);
	fd2 = open_infiles(global, redis, &last2);
	if (fd2 == -1)
		return (fd2);
	if (fd1 != -2 && fd2 != -2)
	{
		if (last1 > last2)
			return (fd1);
		else
			return (fd2);
	}
	if (fd1 > -1)
		return (fd1);
	return (fd2);
}

static int	write_to_file(t_global *global, t_redis *redis)
{
	t_redis	*tmp;
	t_redis	*new_redi;
	int		fd;

	tmp = redis;
	fd = -2;
	while (tmp)
	{
		if (tmp->type == FILE_APPEND)
		{
			close (fd);
			new_redi = redis_expander(global, tmp);
			fd = append_output(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);
		}
		else if (tmp->type == FILE_OUT)
		{
			close (fd);
			new_redi = redis_expander(global, tmp);
			fd = output_redirection(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);	
		}
		tmp = tmp->next;
	}
	return (fd);
}

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
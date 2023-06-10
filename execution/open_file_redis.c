/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_redis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:55:21 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/08 08:24:06 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// for heredoc i have to add a variable that will 
// tell us if we have to expand or not
int	open_heredoc(t_redis *redis, int *need_expand, int *last_heredoc)
{
	t_redis	*tmp;
	int		fd;
	int		i;

	fd = -1;
	i = 0;
	//to add later
	(void)need_expand;
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

int	open_infiles(t_redis *redis, int *last_heredoc)
{
	t_redis	*tmp;
	int		fd;
	int		i;

	tmp = redis;
	fd = -1;
	i = 0;
	while (tmp)
	{
		close (fd);
		if (tmp->type == FILE_IN)
		{
			*last_heredoc = i;
			fd = input_redirection(tmp->str);
			if (fd == -1)
				return (-1);
		}
		i++;
		tmp = tmp->next;
	}
	return (fd);
}

int	read_from_file(t_redis *redis, int *last_heredoc)
{
	int	fd1;
	int	fd2;
	int	last1;
	int	last2;
	int	need_expand;

	fd1 = open_heredoc(redis, &need_expand, &last1);
	if (fd1 == -1)
		return (-1);
	fd2 = open_infiles(redis, &last2);
	if (fd2 == -1)
		return (-1);
	if (last1 > last2)
		return (fd1);
	return (fd2);
}

int	write_to_file(t_redis *redis)
{
	t_redis	*tmp;
	int		fd;

	tmp = redis;
	fd = -2;
	while (tmp)
	{
		close (fd);
		if (tmp->type == FILE_APPEND)
		{
			fd = append_output(tmp->str);
			if (fd == -1)
				return (-1);
		}
		else if (tmp->type == FILE_OUT)
		{
			fd = output_redirection(tmp->str);
			if (fd == -1)
				return (-1);	
		}
		tmp = tmp->next;
	}
	return (fd);
}

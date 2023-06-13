/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:25:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/13 22:00:02 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(t_global *global)
{
	if (pipe(global->pipe) == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
}

void	close_pipe(t_global *global, int count, int i)
{
	if (i > 0)
	{
		if (close(global->prev_fd) == -1)
		{
			global_free(global);
			print_error(NULL, NULL, 1);
		}
	}
	if (i < count)
		global->prev_fd = global->pipe[0];
	if (i < count - 1)
	{
		if (close(global->pipe[1]) == -1)
		{
			global_free(global);
			print_error(NULL, NULL, 1);
		}
	}
}

void	read_write_pipe(t_global *global, int i, int count)
{
	if (count > 1)
	{
		if (i > 0)
		{
			dup2(global->prev_fd, 0);
			close (global->prev_fd);
		}
		if (i < count - 1)
		{
			dup2(global->pipe[1], 1);
			close (global->pipe[1]);
		}
		close(global->pipe[0]);
	}
}

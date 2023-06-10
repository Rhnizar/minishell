/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:25:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/10 18:20:11 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(t_global *global)
{
	// if (pipe(global->pipe) == -1 || pipe(global->pipe + 2) == -1)
	if (pipe(global->pipe) == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
}

void	close_pipes(t_global *global)
{
	(void)global;
	// close(global->pipe[0]);
	// close(global->pipe[1]);
	// close(global->pipe[2]);
	// close(global->pipe[3]);
	// int	i;

	// i = -1;
	// while (++i < 4)
	// {
	// 	if (close (global->pipe[i]) == -1)
	// 	{
	// 		global_free(global);
	// 		print_error(NULL, NULL, 1);
	// 	}
	// }
}

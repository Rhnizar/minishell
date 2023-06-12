/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:25:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/12 21:42:51 by kchaouki         ###   ########.fr       */
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

void	close_pipe(t_global *global)
{
	if (close(global->pipe[0]) == -1 || close(global->pipe[1]) == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
}

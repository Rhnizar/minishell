/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:01:31 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/01 16:54:22 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_wait(t_pipex pipex)
// {
// 	int	status_code;

// 	pipex.cmd_id = -1;
// 	status_code = 0;
// 	while (++(pipex.cmd_id) < pipex.cmd_num)
// 		waitpid(pipex.pid[pipex.cmd_id], &status_code, 0);
// 	if ((status_code >> 8) > 0)
// 		exit(status_code >> 8);
// }

void	exec_commands(t_list *cmd_list)
{
	while (cmd_list)
	{
		cmd_list = cmd_list->next;
	}
	// create_pipes(&pipex);
	// while (++(pipex.cmd_id) < pipex.cmd_num)
	// {
	// 	pipex.pid[pipex.cmd_id] = fork();
	// 	if (pipex.pid[pipex.cmd_id] == -1)
	// 	{
	// 		ft_free_all(&pipex);
	// 		print_error(NULL, NULL, 1);
	// 	}
	// 	if (pipex.pid[pipex.cmd_id] == 0)
	// 	{
	// 		manage_pipes(&pipex);
	// 		get_commands(&pipex);
	// 		if (execve(pipex.valid_path, pipex.cmd_args, pipex.env) == -1)
	// 		{
	// 			ft_free_all(&pipex);
	// 			print_error(NULL, NULL, 1);
	// 		}
	// 	}
	// }
	// close_pipes(&pipex);
	// ft_wait(pipex);
}

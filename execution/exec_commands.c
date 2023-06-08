/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:01:31 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/08 20:11:39 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait(t_global *global, int nbr_cmd)
{
	int	status_code;
	int	i;

	i = -1;
	status_code = 0;
	while (++i < nbr_cmd)
		waitpid(global->pid[i], &status_code, 0);
	if ((status_code >> 8) > 0)
		exit(status_code >> 8);
}

int	count_nbr_commands(t_cmdshell *all_cmds)
{
	t_cmdshell	*tmp;
	int			count;

	tmp = all_cmds;
	count = 0;
	while (tmp && (tmp->cmds->operator == PIPE || tmp->cmds->operator == -1))
	{
		count++;		
		tmp = tmp->next;
	}
	return (count);
}

void	create_pipes(t_global *global)
{
	if (pipe(global->tube) == -1 || pipe(global->tube + 2) == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
}

void	close_pipes(t_global *global)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (close (global->tube[i]) == -1)
		{
			global_free(global);
			print_error(NULL, NULL, 1);
		}
	}
}

void	exec_commands(t_global **global, t_cmdshell **all_cmds)
{
	int	nbr_cmd;
	// int	i;

	nbr_cmd = count_nbr_commands(*all_cmds);
	if (nbr_cmd == 1)
		handle_one_command(*global, all_cmds);
	// else
	// {
	// 	create_pipes(global);
	// 	global->pid = ft_calloc(nbr_cmd, sizeof(int));
	// 	if (!global->pid)
	// 	{
	// 		//error with malloc free all
	// 		print_error(NULL, NULL, 1); 
	// 	}
	// 	i = -1;
	// 	while (++i < nbr_cmd && (*all_cmds) && (*all_cmds)->cmds->operator == PIPE)
	// 	{
	// 		global->pid[i] = fork();
	// 		if (global->pid[i] == -1)
	// 		{
	// 			// free all
	// 			print_error(NULL, NULL, 1);
	// 		}
	// 		if (global->pid[i] == 0)
	// 		{
	// 			// child
	// 		}
	// 		all_cmds = (*all_cmds)->next;
	// 	}
	// 	free (global->pid);	
	// 	close_pipes(global);
	// }
}

void	execution(t_global **global)
{
	t_cmdshell	*all_cmds;

	all_cmds = (*global)->all_commands;
	while (all_cmds)
	{
		exec_commands(global, &all_cmds);
		if (!all_cmds)
			break ;
		all_cmds = all_cmds->next;
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

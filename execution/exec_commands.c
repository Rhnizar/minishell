/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:01:31 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/10 23:48:42 by rrhnizar         ###   ########.fr       */
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

void	execution(t_global *global)
{
	t_cmdshell	*all_cmds;
	pid_t		pid;
	int			count;
	int			i;
	int			exit_status;

	// cmd1 | cmd2 | cmd3 || cmd4 | cmd5 && cmd6 | cmd7
	all_cmds = global->all_commands;
	exit_status = 0;
	count = count_nbr_commands(all_cmds);
	i = 0;
	global->pid = malloc(sizeof(pid_t) * count);
	while(i != count && all_cmds)
	{
		all_cmds->cmds->args = args_expander(global, all_cmds->cmds->args);
		if (count == 1)
		{
			exec_cmd(global, all_cmds);
			return ;
		}
		// if (all_cmds->prev && all_cmds->prev->cmds->operator == PIPE)
		// {
		// 	global->fd = dup(global->pipe[0]);
		// 	close(global->pipe[0]);
		// 	close(global->pipe[1]);
		// }
		create_pipes(global);
		pid = fork();
		if (pid == -1)
		{
			printf("error the fork \n");
			exit(1);
		}
		if (pid == 0)
		{
			exec_cmd_with_pipe(global, all_cmds);
		}
		global->pid[i++] = pid;
		all_cmds = all_cmds->next;
	}
	i = 0;
	while(i != count)
	{
		waitpid(global->pid[i++], NULL, 0);
	}
	close(global->pipe[0]);
	close(global->pipe[1]);
	if (exit_status == 2)
		global->exit_status = 130;
	else
		global->exit_status = exit_status >> 8;
	signal(SIGINT, sig_handl);
		
	// while (all_cmds)
	// {
	// 	all_cmds->cmds->args = args_expander(global, all_cmds->cmds->args);
	// 	handle_one_command(global, all_cmds);
	// 	all_cmds = all_cmds->next;
	// }
}

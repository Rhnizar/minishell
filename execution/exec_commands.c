/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:01:31 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/10 12:36:11 by rrhnizar         ###   ########.fr       */
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

	// cmd1 | cmd2 | cmd3 || cmd4 | cmd5 && cmd6 | cmd7
	all_cmds = global->all_commands;
		
	// if ((*global)->all_commands->cmds->operator == pipe )
		// tab9 pipe 

	while (all_cmds)
	{
		all_cmds->cmds->args = args_expander(global, all_cmds->cmds->args);
		// if (all_cmds->cmds->operator == PIPE)
		// 	create_pipes(global);
		handle_one_command(global, all_cmds);
		// if (all_cmds->cmds->operator == PIPE)
		// 	close_pipes(global);
		// exec_commands(global, &all_cmds);
		all_cmds = all_cmds->next;
	}
}

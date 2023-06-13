/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:01:31 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/13 22:01:41 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_nbr_commands(t_cmdshell *all_cmds)
{
	t_cmdshell	*tmp;
	int			count;

	tmp = all_cmds;
	count = 0;
	while (tmp)
	{
		count++;
		if (tmp->cmds->operator == AND || tmp->cmds->operator == OR)
			break ;
		tmp = tmp->next;
	}
	return (count);
}

void	fill_exit_status(t_global *global, int count)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 0;
	while (i != count)
		waitpid(global->pid[i++], &exit_status, 0);
	if (exit_status == 2)
		global->exit_status = 130;
	else
		global->exit_status = exit_status >> 8;
	free(global->pid);
	signal(SIGINT, sig_handl);
}

void	exec_one_command(t_global *global, t_cmdshell *cmd, int i, int count)
{
	if (count == 1 && cmd->cmds->args && is_builtin(cmd->cmds->args->str))
	{
		builtins(global, cmd);
		return ;
	}
	if (cmd->cmds->subshell)
		run_subshell(global, cmd->cmds->subshell, i, count);
	else
		not_builtin(global, cmd, i, count);
}

t_cmdshell	*exec_commands(t_global *global, t_cmdshell *all_cmds)
{
	int			count;
	int			i;

	i = 0;
	count = count_nbr_commands(all_cmds);
	global->pid = malloc(sizeof(pid_t) * count);
	if (!global->pid)
		print_error(NULL, NULL, 1);
	global->prev_fd = -1;
	while (all_cmds && i != count)
	{
		if (i < count - 1)
			create_pipe(global);
		all_cmds->cmds->args = args_expander(global, all_cmds->cmds->args);
		exec_one_command(global, all_cmds, i, count);	
		if (count > 1)
			close_pipe(global, count, i);
		i++;
		all_cmds = all_cmds->next;
	}
	fill_exit_status(global, count);
	return (all_cmds);
}

int	count_or(t_cmdshell *cmds)
{
	t_cmdshell	*tmp_cmds;
	int			count;

	tmp_cmds = cmds;
	count = 0;
	while (tmp_cmds)
	{
		if (tmp_cmds->cmds->operator == OR)
			count++;
		tmp_cmds  = tmp_cmds->next;
	}
	return (count);
}

int	_execution(t_global *global, t_cmdshell **all_cmds, int cou_or)
{
	if (global->exit_status == 0 && (*all_cmds)->prev->cmds->operator == AND)
		return (2);
	else if (global->exit_status != 0 && (*all_cmds)->prev->cmds->operator == AND)
	{
		if (cou_or != 0)
		{
			while((*all_cmds)->cmds->operator != OR)
				(*all_cmds) = (*all_cmds)->next;
			(*all_cmds) = (*all_cmds)->next;
			return (2);
		}
		return (1);
	}
	else if (global->exit_status == 0 && (*all_cmds)->prev->cmds->operator == OR)
		return (1);
	else if (global->exit_status != 0 && (*all_cmds)->prev->cmds->operator == OR)
		return (2);
	return (1);
}

void	execution(t_global *global)
{
	t_cmdshell	*all_cmds;
	int			cou_or;

	all_cmds = global->all_commands;
	cou_or = count_or(all_cmds);
	while (1)
	{
		all_cmds = exec_commands(global, all_cmds);
		if (all_cmds)
		{
			if (_execution(global, &all_cmds, cou_or) == 2)
				continue ;
			else
				break ;
		}
		else
			break ;
	}
}

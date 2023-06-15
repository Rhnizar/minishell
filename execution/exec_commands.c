/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:01:31 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/15 20:08:50 by rrhnizar         ###   ########.fr       */
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

	i = 0;
	exit_status = 0;
	if (count == 1 && global->all_commands->cmds->args \
		&& is_builtin(global->all_commands->cmds->args->str))
	{
		free(global->pid);
		return ;
	}
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
	int	fd_tmp;

	fd_tmp = -1;
	if (count == 1 && cmd->cmds->args && is_builtin(cmd->cmds->args->str))
	{
		fd_tmp = manage_redirection_builtins(global, cmd);
		if (fd_tmp == -2)
			global->exit_status = 1;
		else
		{
			builtins(global, cmd);
			if (fd_tmp != -1)
			{
				dup2(fd_tmp, 1);
				close (fd_tmp);
			}
		}
		return ;
	}
	if (cmd->cmds->subshell)
		run_subshell(global, cmd, i, count);
	else
		not_builtin(global, cmd, i, count);
}

t_cmdshell	*exec_commands(t_global *global, t_cmdshell *all_cmds)
{
	int			count;
	int			i;

	i = 0;
	count = count_nbr_commands(all_cmds);
	global->pid = ft_calloc(count, sizeof(pid_t));
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
		if (all_cmds->cmds->fd_herdoc != -2 && \
		close (all_cmds->cmds->fd_herdoc) == -1)
			print_error(NULL, NULL, 1);
		i++;
		all_cmds = all_cmds->next;
	}
	fill_exit_status(global, count);
	return (all_cmds);
}

void	execution(t_global *global)
{
	t_cmdshell	*all_cmds;
	int			cou_or;
	int			cou_and;

	all_cmds = global->all_commands;
	cou_or = count_or(all_cmds);
	cou_and = count_and(all_cmds);
	while (1)
	{
		all_cmds = exec_commands(global, all_cmds);
		if (all_cmds)
		{
			if (and(global, &all_cmds, cou_or) == 2)
				continue ;
			else if (and(global, &all_cmds, cou_or) == 1)
				break ;
			else if (or(global, &all_cmds, cou_and) == 2)
				continue ;
			else if (or(global, &all_cmds, cou_and) == 1)
				break ;
		}
		else
			break ;
	}
}

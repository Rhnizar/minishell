/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:01:31 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/12 23:39:59 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_nbr_commands(t_cmdshell *all_cmds)
{
	t_cmdshell	*tmp;
	int			count;

	tmp = all_cmds;
	count = 0;
	while (tmp && (tmp->cmds->operator == PIPE || tmp->cmds->operator == -1 \
		|| tmp->cmds->operator == AND || tmp->cmds->operator == OR))
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

void	exec_cmd(t_global *global, t_cmdshell *cmd, int i, int count)
{
	cmd->cmds->args = args_expander(global, cmd->cmds->args);
	if (count == 1 && cmd->cmds->args && is_builtin(cmd->cmds->args->str))
	{
		builtins(global, cmd);
		return ;
	}
	if (i < count - 1)
		create_pipe(global);
	not_builtin(global, cmd, i, count);
}

t_cmdshell	*exec_cmds(t_global *global, t_cmdshell *all_cmds)
{
	int			count;
	int			i;

	count = count_nbr_commands(all_cmds);
	i = 0;
	global->pid = malloc(sizeof(pid_t) * count);
	if (!global->pid)
		print_error(NULL, NULL, 1);
	global->prev_fd = -1;
	while (all_cmds && i != count)
	{
		exec_cmd(global, all_cmds, i, count);
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

// char	*remove_parantheces(char *str)
// {
// 	char	*output;
// 	int		count;
// 	int		i;
// 	int		j;

// 	i = 1;
// 	j = 0;
// 	count = ft_strlen(str);
// 	output = malloc(sizeof(char) * count - 1);
// 	if (!output)
// 		print_error(NULL, NULL, 1);
// 	while (i < count - 1)
// 		output[j++] = str[i++];
// 	output[j] = '\0';
// 	return (output);
// }

// void	run_subshell(t_global *global, char *subshell)
// {
// 	pid_t	pid;
// 	int		status;

// 	status = 0;
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		global_free(global);
// 		print_error(NULL, NULL, 1);
// 	}
// 	else if (pid == 0)
// 	{
// 		//call subshell
// 		// remove_parantheces(subshell);
// 	}
// 	waitpid(pid, &status, 0);
// 	if (status == 2)
// 		global->exit_status = 130;
// 	else
// 		global->exit_status = status >> 8;
// }

void	execution(t_global *global)
{	
	t_cmdshell	*all_cmds;
	int			cou_or;

	all_cmds = global->all_commands;
	cou_or = count_or(all_cmds);
	while (1)
	{
		// if (all_cmds->cmds->subshell)
		// 	run_subshell(global, all_cmds->cmds->subshell);
		// else
			all_cmds = exec_cmds(global, all_cmds);
		if (all_cmds)
		{
			if (global->exit_status == 0 && all_cmds->prev->cmds->operator == AND)
				continue ;
			else if (global->exit_status != 0 && all_cmds->prev->cmds->operator == AND)
			{
				if (cou_or != 0)
				{
					while(all_cmds->cmds->operator != OR)
						all_cmds = all_cmds->next;
					all_cmds = all_cmds->next;
					continue ;
				}
				break ;
			}
			else if (global->exit_status == 0 && all_cmds->prev->cmds->operator == OR)
				break ;
			else if (global->exit_status != 0 && all_cmds->prev->cmds->operator == OR)
				continue ;
		}
		else
			break ;
	}
}

//ls | cat -e| wcc -l && ls || echo test  hadi khasha lkhdma
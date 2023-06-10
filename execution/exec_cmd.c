/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:16:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/10 23:42:14 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_builtin(t_global *global, t_cmdshell *all_cmds)
{
	int			exit_status;
	t_recipe	recipe;
	pid_t		pid;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		recipe = prepare_command(global, all_cmds);
		if (execve(recipe.command, recipe.args, recipe.envp) == -1)
		{
			global_free(global);
			print_error(NULL, NULL, 1);
		}
	}
	waitpid(pid, &exit_status, 0);
	if (exit_status == 2)
		global->exit_status = 130;
	else
		global->exit_status = exit_status >> 8;
	signal(SIGINT, sig_handl);
}

void	exec_cmd(t_global *global, t_cmdshell *all_cmds)
{
	if (all_cmds->cmds->args)
	{
		if (is_builtin(all_cmds->cmds->args->str))
		{
			builtins(global, all_cmds);
		}
		else
			not_builtin(global, all_cmds);
	}
}

void	not_builtin_pipe(t_global *global, t_cmdshell *all_cmds)
{
	t_recipe	recipe;
	
	signal(SIGINT, SIG_DFL);
	if (all_cmds->cmds->operator == PIPE)
	{
		dup2(global->fd, 0);
		dup2(global->pipe[1], 1);
		close(global->pipe[0]);
	}
	else if (all_cmds->prev && all_cmds->prev->cmds->operator == PIPE)
	{
		dup2(global->pipe[0], 0);
		close(global->pipe[1]);
	}
	recipe = prepare_command(global, all_cmds);
	if (execve(recipe.command, recipe.args, recipe.envp) == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
}

void	exec_cmd_with_pipe(t_global *global, t_cmdshell *all_cmds)
{
	if (all_cmds->cmds->args)
	{
		if (is_builtin(all_cmds->cmds->args->str))
		{
			if (all_cmds->cmds->operator == PIPE)
			{
				dup2(global->pipe[1], 1);
				close(global->pipe[0]);
				close(global->pipe[1]);
				builtins(global, all_cmds);
				exit(0);
			}
			else if (all_cmds->prev && all_cmds->prev->cmds->operator == PIPE)
			{
				dup2(global->pipe[0], 0);
				close(global->pipe[0]);
				close(global->pipe[1]);
				builtins(global, all_cmds);
				exit(0);
			}
			else
				builtins(global, all_cmds);
		}
		else
			not_builtin_pipe(global, all_cmds);
	}
}
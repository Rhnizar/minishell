/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:28:42 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/10 23:43:42 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_builtinn(t_global *global, t_cmdshell *all_cmds)
{
	int			exit_status;
	t_recipe	recipe;
	pid_t		pid;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	if (all_cmds->cmds->operator == PIPE)
	{
		if (all_cmds->prev && all_cmds->prev->cmds->operator == PIPE)
		{
			global->fd = dup(global->pipe[0]);
			close(global->pipe[0]);
			close(global->pipe[1]);
		}
		create_pipes(global);
	}
	pid = fork();
	if (pid == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (all_cmds->cmds->operator == PIPE)
		{
			if (dup2(global->fd, 0) == -1)
			{
				printf("error\n");
				exit(1);
			}
			dup2(global->pipe[1], 1);
			close(global->pipe[0]);
		}
		else if (all_cmds->prev && all_cmds->prev->cmds->operator == PIPE)
		{
			dup2(global->pipe[0], 0);
			close(global->pipe[1]);
		}
		// if (manage_redirection(global, all_cmds->cmds->redis))
		// exit(1);
		recipe = prepare_command(global, all_cmds);
		if (execve(recipe.command, recipe.args, recipe.envp) == -1)
		{
			global_free(global);
			print_error(NULL, NULL, 1);
		}
	}
	if (all_cmds->next == NULL)
	{
		close(global->pipe[0]);
		close(global->pipe[1]);
	}
	waitpid(pid, &exit_status, 0);
	if (exit_status == 2)
		global->exit_status = 130;
	else
		global->exit_status = exit_status >> 8;
	signal(SIGINT, sig_handl);
}

void	handle_one_command(t_global *global, t_cmdshell *all_cmds)
{
	pid_t	pid;
	int		ex_st;

	if (all_cmds->cmds->args)
	{
		if (is_builtin(all_cmds->cmds->args->str))
		{
			if (all_cmds->cmds->operator == PIPE)
			{
				create_pipes(global);
				pid = fork();
				if (pid == 0)
				{
					dup2(global->pipe[1], 1);
					close(global->pipe[0]);
					close(global->pipe[1]);
					builtins(global, all_cmds);
					exit(0);
				}
				waitpid(pid, &ex_st, 0);
			}
			else if (all_cmds->prev && all_cmds->prev->cmds->operator == PIPE)
			{
				pid = fork();
				if (pid == 0)
				{
					dup2(global->pipe[0], 0);
					close(global->pipe[0]);
					close(global->pipe[1]);
					builtins(global, all_cmds);
					exit(0);
				}
				waitpid(pid, &ex_st, 0);
			}
			else
				builtins(global, all_cmds);
			if (all_cmds->next == NULL)
			{
				close(global->pipe[0]);
				close(global->pipe[1]);
			}
			/*-------    blane dyal redirections ghadi itktb fi ----------------*/
		}
		else
		{
			// printf("noo\n");
			not_builtinn(global, all_cmds);
		}
	}
}


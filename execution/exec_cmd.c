/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:16:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/12 23:52:34 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	not_builtin(t_global *global, t_cmdshell *all_cmds)
// {
// 	int			exit_status;
// 	t_recipe	recipe;
// 	pid_t		pid;

// 	exit_status = 0;
// 	signal(SIGINT, SIG_IGN);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		global_free(global);
// 		print_error(NULL, NULL, 1);
// 	}
// 	else if (pid == 0)
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		recipe = prepare_command(global, all_cmds);
// 		if (execve(recipe.command, recipe.args, recipe.envp) == -1)
// 		{
// 			global_free(global);
// 			print_error(NULL, NULL, 1);
// 		}
// 	}
// 	waitpid(pid, &exit_status, 0);
// 	if (exit_status == 2)
// 		global->exit_status = 130;
// 	else
// 		global->exit_status = exit_status >> 8;
// 	signal(SIGINT, sig_handl);
// }

void	not_builtin(t_global *global, t_cmdshell *all_cmds, int i, int count)
{
	int			exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	global->pid[i] = fork();
	if (global->pid[i] == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
	else if (global->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		exec_cmd_with_pipe(global, all_cmds, i, count);
	}
	if (i > 0)
        close(global->prev_fd);
    if (i < count)
        global->prev_fd = global->pipe[0];
    close(global->pipe[1]);
}

void	with_pipe(t_global *global, int i, int count)
{
	if (i > 0)
    {
        dup2(global->prev_fd, 0);
        close (global->prev_fd);
    }
	if (i < count - 1)
    {
        dup2(global->pipe[1], 1);
        close (global->pipe[1]);
    }
	close(global->pipe[0]);
}

void	exec_cmd_with_pipe(t_global *global, t_cmdshell *all_cmds, int i, int count)
{
	t_recipe	recipe;

	if (count > 1)
		with_pipe(global, i, count);
	if (all_cmds->cmds->args && is_builtin(all_cmds->cmds->args->str))
	{
		builtins(global, all_cmds);
		exit(global->exit_status);
	}
	else
	{
		if (manage_redirection(global, all_cmds->cmds->redis))
			exit(1);
		recipe = prepare_command(global, all_cmds);
    	if (execve(recipe.command, recipe.args, recipe.envp) == -1)
    	{
    	    global_free(global);
    	    print_error(NULL, NULL, 1);
    	}
	}
}

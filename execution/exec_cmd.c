/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:16:30 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/14 11:12:06 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd_with_pipe(t_global *global, t_cmdshell *all_cmds, \
	int i, int count)
{
	t_recipe	recipe;

	if (count > 1)
		read_write_pipe(global, i, count);
	if (all_cmds->cmds->args && is_builtin(all_cmds->cmds->args->str))
	{
		builtins(global, all_cmds);
		exit(global->exit_status);
	}
	else
	{
		if (manage_redirection(global, all_cmds->cmds->redis))
			printf("redis\n");
		recipe = prepare_command(global, all_cmds);
		if (execve(recipe.command, recipe.args, recipe.envp) == -1)
		{
			global_free(global);
			print_error(NULL, NULL, 1);
		}
	}
}

void	not_builtin(t_global *global, t_cmdshell *all_cmds, int i, int count)
{
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
}

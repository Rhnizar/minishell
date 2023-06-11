/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:28:42 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/10 16:54:37 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void builtins(t_global *global, t_cmdshell *all_cmds)
{
	char	*command;
	t_args	*args;

	args = args_expander(global, all_cmds->cmds->args);
	command = all_cmds->cmds->args->str;
	if (ft_strncmp("export", command, ft_strlen("export")) == 0)
		add_to_export_or_print(global->env, global->export, args);
	if (ft_strncmp("env", command, ft_strlen("env")) == 0)
		print_env(global->env);
	if (ft_strncmp("unset", command, ft_strlen("unset")) == 0)
		unset(&global->env, &global->export, args);
	if (ft_strncmp("exit", command, ft_strlen("exit")) == 0)
		exitt(args);
	if (ft_strncmp("pwd", command, ft_strlen("pwd")) == 0)
		pwd(global);
	if (ft_strncmp("cd", command, ft_strlen("cd")) == 0)
		cd(global, args, global->export);
	if (ft_strncmp("echo", command, ft_strlen("echo")) == 0)
		echo(global, args);
	free_args(args); //  this free is useless here becaue i'am free args in function free_commands .
}

static int	is_builtin(char *token)
{
	// if (!ft_strcmp(token, "echo"))
	// 	return (1);
	if (!ft_strcmp(token, "cd"))
		return (1);
	else if (!ft_strcmp(token, "pwd"))
		return (1);
	else if (!ft_strcmp(token, "env"))
		return (1);
	else if (!ft_strcmp(token, "export"))
		return (1);
	else if (!ft_strcmp(token, "unset"))
		return (1);
	else if (!ft_strcmp(token, "exit"))
		return (1);
	return (0);
}

static int	count_env(t_env *env)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*ft_join_env(char *s1, char *s2)
{
	char	*output;
	int		i;

	output = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!output)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		output[i++] = *s1++;
	output[i++] = '=';
	while (s2 && *s2)
		output[i++] = *s2++;
	output[i] = '\0';
	return (output);
}

char	**get_env(t_env *env)
{
	char	**output;
	int		i;

	output = malloc(sizeof(char *) * (count_env(env) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (env)
	{
		output[i++] = ft_join_env(env->var, env->value);
		env = env->next;
	}
	output[i] = NULL;
	return (output);
}

static int	count_args(t_args *args)
{
	t_args	*tmp;
	int		count;

	count = 0;
	tmp = args;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**get_args(t_global	*global, t_args	*args)
{
	char	**output;
	t_args	*new_args;
	t_args	*tmp;
	int		i;

	new_args = args_expander(global, args);
	output = malloc(sizeof(char *) * (count_args(new_args) + 1));
	if (!output)
		return (NULL);
	i = 0;
	tmp = new_args;
	while (tmp)
	{
		output[i++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	output[i] = NULL;
	free_args(new_args);
	return (output);	
}

t_recipe	prepare_command(t_global *global, t_cmdshell *all_cmds)
{
	t_recipe	output;
	char		**paths;

	paths = get_paths(global->env);
	output.args = get_args(global, all_cmds->cmds->args);
	output.command = valid_command_path(paths, output.args[0]); 
	free_double_ptr(paths);
	output.envp = get_env(global->env);
	return (output);
}

void	handle_one_command(t_global *global, t_cmdshell **all_cmds)
{
	// int o_stdout;
	// int o_stdin;
	// int exec_cmd;
	// int	fd1;
	// int	fd2;

	// o_stdout = dup(STDOUT_FILENO);
	// o_stdin = dup(STDIN_FILENO);
	// exec_cmd = 1;
	if (is_builtin((*all_cmds)->cmds->args->str))
	{
		// fd1 = read_from_file(global, (*all_cmds)->cmds->redis);
		// if (fd1 != -2)
		// {
		// 	if (fd1 == -1)
		// 		exec_cmd = 0;
		// 	else
		// 	{
		// 		if (dup2(fd1, STDIN_FILENO) == -1)
		// 		{
		// 			global_free(global);
		// 			print_error(NULL, NULL, -1);
		// 		}
		// 	}
		// }
		// fd2 = write_to_file(global, (*all_cmds)->cmds->redis);
		// if (fd2 != -2)
		// {
		// 	if (fd2 == -1)
		// 		exec_cmd = 0;
		// 	else
		// 	{
		// 		if (dup2(fd2, STDOUT_FILENO) == -1)
		// 		{
		// 			global_free(global);
		// 			print_error(NULL, NULL, -1);
		// 		}
		// 	}
		// }
		// if (exec_cmd)
		// {
		//	 builtins(global, *all_cmds);
		// 	if (fd1 > 0)
		// 	{
		// 		if (dup2(o_stdin, STDIN_FILENO) == -1)
		// 		{
		// 			global_free(global);
		// 			print_error(NULL, NULL, 1);
		// 		}
		// 		close(fd1);
		// 	}
		// 	if (fd2 > 0)
		// 	{
		// 		if (dup2(o_stdout, STDOUT_FILENO) == -1)
		// 		{
		// 			global_free(global);
		// 			print_error(NULL, NULL, 1);
		// 		}
		// 		close(fd2);
		// 	}			
		// }
		builtins(global, *all_cmds);
		(*all_cmds) = (*all_cmds)->next;
	}
	else
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
			if (manage_redirection(global, (*all_cmds)->cmds->redis))
				exit (1);
			recipe = prepare_command(global, (*all_cmds));
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
}

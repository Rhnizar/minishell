/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:28:42 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/08 16:01:00 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_heredoc(t_redis *redis, int *need_expand, int *last_heredoc)
{
	t_redis	*tmp;
	int		fd;
	int		i;

	fd = -2;
	i = 0;
	//to add later
	(void)need_expand;
	tmp = redis;
	while (tmp)
	{
		unlink ("/tmp/here_doc.txt");
		if (tmp->type == HEREDOC)
		{
			(*last_heredoc) = i;
			fd = here_doc(redis->str);
			if (fd == -1)
				return (-1);
		}
		i++;
		tmp = tmp->next;
	}
	return (fd);
}

int	open_infiles(t_global *global, t_redis *redis, int *last_heredoc)
{
	t_redis	*tmp;
	t_redis	*new_redi;
	int		fd;
	int		i;

	tmp = redis;
	fd = -2;
	i = 0;
	while (tmp)
	{
		close (fd);
		if (tmp->type == FILE_IN)
		{
			*last_heredoc = i;
			new_redi = redis_expander(global, redis);
			fd = input_redirection(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);
		}
		i++;
		tmp = tmp->next;
	}
	return (fd);
}

int	read_from_file(t_global *global, t_redis *redis)
{
	int	fd1;
	int	fd2;
	int	last1;
	int	last2;
	int	need_expand;

	fd1 = open_heredoc(redis, &need_expand, &last1);
	if (fd1 < 0)
		return (fd1);
	fd2 = open_infiles(global, redis, &last2);
	if (fd2 < 0)
		return (fd2);
	if (last1 > last2)
		return (fd1);
	return (fd2);
}

int	write_to_file(t_global *global, t_redis *redis)
{
	t_redis	*tmp;
	t_redis	*new_redi;
	int		fd;

	tmp = redis;
	fd = -2;
	while (tmp)
	{
		close (fd);
		if (tmp->type == FILE_APPEND)
		{
			new_redi = redis_expander(global, redis);
			fd = append_output(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);
		}
		else if (tmp->type == FILE_OUT)
		{
			new_redi = redis_expander(global, redis);
			fd = output_redirection(new_redi->str);
			free_redis(new_redi);
			if (fd == -1)
				return (-1);	
		}
		tmp = tmp->next;
	}
	return (fd);
}

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
		echo(args);
	free_args(args);
}

static int	is_builtin(char *token)
{
	if (!ft_strcmp(token, "echo"))
		return (1);
	else if (!ft_strcmp(token, "cd"))
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
	char		*cmd;

	paths = get_paths(global->env);
	cmd = all_cmds->cmds->args->str;
	output.command = valid_command_path(paths, cmd);
	free_double_ptr(paths);
	if (!output.command)
		print_error(ECNF, cmd, 127);
	if (output.command && access(output.command, X_OK))
		print_error(EPD, cmd, 126);
	output.envp = get_env(global->env);
	output.args = get_args(global, all_cmds->cmds->args);
	return (output);
}

int	manage_redirection(t_global *global, t_redis *redis)
{
	int	fd_read;
	int	fd_write;

	fd_read = read_from_file(global, redis);
	if (fd_read != -2)
	{
		if (fd_read == -1)
			return (1);
		if (dup2(fd_read, STDIN_FILENO) == -1)
			return (print_error(NULL, NULL, -1), 1);
	}
	fd_write = write_to_file(global, redis);
	if (fd_write != -2)
	{
		if (fd_write == -1)
			return (1);
		if (dup2(fd_write, STDOUT_FILENO) == -1)
			return (print_error(NULL, NULL, -1), 1);
	}
	return (0);
}

void	handle_one_command(t_global *global, t_cmdshell **all_cmds)
{
	int o_stdout;
	int o_stdin;
	int exec_cmd;
	int	fd1;
	int	fd2;

	o_stdout = dup(STDOUT_FILENO);
	o_stdin = dup(STDIN_FILENO);
	exec_cmd = 1;
	if (is_builtin((*all_cmds)->cmds->args->str))
	{
		fd1 = read_from_file(global, (*all_cmds)->cmds->redis);
		if (fd1 != -2)
		{
			if (fd1 == -1)
				exec_cmd = 0;
			else
			{
				if (dup2(fd1, STDIN_FILENO) == -1)
				{
					global_free(global);
					print_error(NULL, NULL, -1);
				}
			}
		}
		fd2 = write_to_file(global, (*all_cmds)->cmds->redis);
		if (fd2 != -2)
		{
			if (fd2 == -1)
				exec_cmd = 0;
			else
			{
				if (dup2(fd2, STDOUT_FILENO) == -1)
				{
					global_free(global);
					print_error(NULL, NULL, -1);
				}
			}
		}
		if (exec_cmd)
		{
			builtins(global, *all_cmds);
			if (fd1 > 0)
			{
				if (dup2(o_stdin, STDIN_FILENO) == -1)
				{
					global_free(global);
					print_error(NULL, NULL, 1);
				}
				close(fd1);
			}
			if (fd2 > 0)
			{
				if (dup2(o_stdout, STDOUT_FILENO) == -1)
				{
					global_free(global);
					print_error(NULL, NULL, 1);
				}
				close(fd2);
			}			
		}
		(*all_cmds) = (*all_cmds)->next;
	}
	else
	{
		int			exit_status;
		t_recipe	recipe;
		pid_t		pid;

		exit_status = 0;
		pid = fork();
		if (pid == -1)
		{
			global_free(global);
			print_error(NULL, NULL, 1);
		}
		if (pid == 0)
		{
			if (manage_redirection(global, (*all_cmds)->cmds->redis))
				exit (1);
			recipe = prepare_command(global, (*all_cmds));
			// printf("command: %s\n", recipe.command);
			// char **tmp1 = recipe.args;
			// int	i = 0;
			// while (tmp1[i])
			// {
			// 	printf("arg[%d]: %s\n", i, tmp1[i]);
			// 	i++;
			// }
			// exit(1);
			if (execve(recipe.command, recipe.args, recipe.envp) == -1)
			{
				global_free(global);
				print_error(NULL, NULL, 1);
			}
		}
		waitpid(pid, &exit_status, 0);
		global->exit_status = exit_status;
	}
}

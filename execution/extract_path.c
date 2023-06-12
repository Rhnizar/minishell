/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:11:01 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/12 23:35:54 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* join a given path with a given command */
static char	*ft_join_command_path(char *path, char *cmd)
{
	char	*output;
	int		i;

	output = malloc(ft_strlen(cmd) + ft_strlen(path) + 2);
	if (!output)
		print_error(NULL, NULL, 1);
	i = 0;
	while (path && *path)
		output[i++] = *path++;
	output[i++] = '/';
	while (cmd && *cmd)
		output[i++] = *cmd++;
	output[i] = '\0';
	return (output);
}

/* get the exact command path */
char	*valid_command_path(char **paths, char *cmd)
{
	char	*command_path;

	command_path = NULL;
	// still need to be handled
	if (access(cmd, F_OK) == 0 && ft_strchr(cmd, '/') && access(cmd, X_OK) == -1)
	{
		print_error(EPD, cmd, 126);
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
			print_error(ENSFD, cmd, 127);
		if (access(cmd, F_OK) == 0)
			print_error(EIAD, cmd, 126);
		return (NULL);
	}
	while (*paths)
	{
		command_path = ft_join_command_path(*paths, cmd);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		command_path = NULL;
		paths++;
	}
	if (!command_path)
		print_error(ECNF, cmd, 127);
	return (NULL);
}

char	**get_paths(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->var, "PATH"))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (ft_split(env->value, ':'));
}

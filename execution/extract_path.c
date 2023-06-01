/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:11:01 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/01 16:08:43 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../minishell.h"

/* join a given path with a given command */
static char	*ft_join_command_path(char *path, char *cmd)
{
	char	*output;
	int		i;

	output = malloc(ft_strlen(cmd) + ft_strlen(path) + 2);
	if (!output)
		return (NULL);
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

	if (access(cmd, F_OK) == 0 && ft_strchr(cmd, '/'))
		return (cmd);
	else if (ft_strchr(cmd, '/'))
		return (NULL);
	else
	{
		while (*paths)
		{
			command_path = ft_join_command_path(*paths, cmd);
			if (access(command_path, F_OK) == 0)
				return (command_path);
			free(command_path);
			paths++;
		}
	}
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

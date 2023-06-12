/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:20:27 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/12 17:12:37 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**get_args(t_cmdshell *cmd)
{
	char	**output;
	t_args	*new_args;
	t_args	*tmp;
	int		i;

	new_args = cmd->cmds->args;
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
	return (output);
}

t_recipe	prepare_command(t_global *global, t_cmdshell *all_cmds)
{
	t_recipe	output;
	char		**paths;

	paths = get_paths(global->env);
	output.args = get_args(all_cmds);
	output.command = valid_command_path(paths, output.args[0]); 
	free_double_ptr(paths);
	output.envp = get_env(global->env);
	return (output);
}

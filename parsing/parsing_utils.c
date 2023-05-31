/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:39:59 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 12:26:55 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_to_str(char *str, char c)
{
	char	*output;
	int		i;

	if (!str)
		output = malloc(2);
	else
		output = malloc(ft_strlen(str) + 2);
	if (!output)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i++] = c;
	output[i] = '\0';
	free (str);
	return (output);
}

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free (str[i++]);
	free(str);
}

void	all_free_parsing(t_global *global)
{
	t_cmdshell	*tmp;

	while (global->all_commands)
	{
		tmp = global->all_commands;
		free_redis(global->all_commands->cmds->redis);
		free_args(global->all_commands->cmds->args);
		free(global->all_commands->cmds->subshell);
		free(global->all_commands->cmds);
		global->all_commands = global->all_commands->next;
		free(tmp);
	}
	free_env(global->env);
	free(global);
}

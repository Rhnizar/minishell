/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils_define2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:03:26 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/23 16:29:59 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_struct_cmds(t_cmds **cmds)
{
	(*cmds)->redis = NULL;
	(*cmds)->args = NULL;
	(*cmds)->subshell = NULL;
	(*cmds)->cmd = NULL;
	return (0);
}

///// command is builtin ////
int	is_builtin(char *token)
{
	if (ft_strcmp(token, "echo"))
		return (1);
	else if (ft_strcmp(token, "cd"))
		return (1);
	else if (ft_strcmp(token, "pwd"))
		return (1);
	else if (ft_strcmp(token, "env"))
		return (1);
	else if (ft_strcmp(token, "export"))
		return (1);
	else if (ft_strcmp(token, "unset"))
		return (1);
	else if (ft_strcmp(token, "exit"))
		return (1);
	return (0);
}


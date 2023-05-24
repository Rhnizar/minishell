/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils_define2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:03:26 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/24 17:05:16 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_struct_cmds(t_cmds **cmds)
{
	(*cmds)->redis = NULL;
	(*cmds)->args = NULL;
	(*cmds)->subshell = NULL;
	(*cmds)->cmd = NULL;
	(*cmds)->operator = -1;
	(*cmds)->is_builtin = -1;
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


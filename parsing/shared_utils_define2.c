/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils_define2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:03:26 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/31 09:43:55 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_cmd_to_list(t_cmdshell **lst, t_cmds *cmds)
{
	t_cmdshell	*new;
	t_cmdshell	*tmp;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return ;
	new->cmds = cmds;
	new->next = NULL;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

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

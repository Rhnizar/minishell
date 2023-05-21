/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:12:05 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/21 14:51:02 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int init1(t_utils **utils, t_args **args, t_redis **redis)
// {
// 	*utils = malloc(sizeof(t_utils));
// 	if (!(*utils))
// 		return (-1);
// 	(*utils)->spl_redi = ft_split("<< < > >>", ' ');
// 	(*utils)->spl_sp_char = ft_split("|| && |", ' ');
// 	return (0);
// }

int	init_struct_cmds(t_cmds **cmds)
{
	// *cmds = malloc(sizeof(t_cmds));
	// if (!(*cmds))
	// 	return (-1);
	(*cmds)->redis = NULL;
	(*cmds)->args = NULL;
	(*cmds)->utils = malloc(sizeof(t_utils));
	if (!((*cmds)->utils))
		return (-1);
	// (*cmds)->utils->spl_redi = ft_split("<< < > >>", ' ');
	(*cmds)->utils->spl_redi = ft_split(">> << < >", ' ');
	(*cmds)->utils->spl_sp_char = ft_split("|| && |", ' ');
	(*cmds)->sp_id = -1;
	(*cmds)->red_id = -1;
	(*cmds)->subshell = NULL;
	(*cmds)->cmd = NULL;
	return (0);
}

int	init_cmds(t_cmdshell *cmdshell)
{
	cmdshell = malloc(sizeof(t_cmdshell));
	if (!cmdshell)
		return (-1);
	init_struct_cmds(&cmdshell->cmds);
	// cmdshell->cmds = malloc(sizeof(t_cmds));
	// if (!cmdshell->cmds)
	// 	return (-1);
	// if (init1(cmdshell->cmds->utils, cmdshell->cmds->args, cmdshell->cmds->redis) == -1)
	// 	return (-1);
	return (0);
}

int	init_global(t_global *glob)
{
	glob->env = malloc(sizeof(t_env));
	if (!glob->env)
		return (-1);
	// if (init_cmds(glob->all_commands) == -1)
	// 	return (-1);
	return (0);
}

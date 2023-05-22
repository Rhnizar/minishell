/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:12:05 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/22 19:03:45 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	init_struct_cmds(t_cmds **cmds)
// {
// 	(*cmds)->redis = NULL;
// 	(*cmds)->args = NULL;
// 	(*cmds)->subshell = NULL;
// 	(*cmds)->cmd = NULL;
// 	return (0);
// }

// int	init_struct_utils(t_utils **utils)
// {
// 	*utils = malloc(sizeof(t_utils));
// 	if (!(*utils))
// 		return (-1);
// 	(*utils)->spl_redi = ft_split(">> << < >", ' ');
// 	if (!((*utils)->spl_redi))
// 		return (-1);
// 	(*utils)->spl_sp_char = ft_split("|| && |", ' ');
// 	if (!((*utils)->spl_sp_char))
// 		return (-1);
// 	(*utils)->sp_id = -1;
// 	(*utils)->red_id = -1;
// 	(*utils)->red_id_prev = -1;
// 	(*utils)->sp_id_prev = -1;
// 	(*utils)->red_id_prev_prev = -1;
// 	return (0);
// }

int	init_global(t_global *glob)
{
	glob->env = malloc(sizeof(t_env));
	if (!glob->env)
		return (-1);
	// if (init_cmds(glob->all_commands) == -1)
	// 	return (-1);
	return (0);
}

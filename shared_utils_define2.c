/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_utils_define2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:03:26 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/22 19:03:50 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct_cmds(t_cmds **cmds)
{
	(*cmds)->redis = NULL;
	(*cmds)->args = NULL;
	(*cmds)->subshell = NULL;
	(*cmds)->cmd = NULL;
	return (0);
}
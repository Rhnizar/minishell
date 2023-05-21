/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:14:25 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/21 09:54:10 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_cmdshell	*fill_list_cmds(t_cmdshell *lst, t_tokens *token)
{
	t_tokens	*tmp;
	t_cmds		*cmds;

	tmp = token;
	cmds = NULL;
	lst = NULL;
	while (tmp)
	{
		init_cmd(&cmds, tmp);
		tmp = fill_struct_cmds(&cmds, tmp);
		create_cmds(&lst, cmds);
		free_double_ptr(cmds->args);
		free_double_ptr(cmds->redi);
		free_double_ptr(cmds->spl_redi);
		free_double_ptr(cmds->spl_sp_char);
		free(cmds);
	}
	return (lst);
}
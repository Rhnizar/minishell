/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:33:58 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/13 12:03:03 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fill_list_cmds(t_cmdshell **lst, t_tokens *tokens)
{
	t_tokens	*tmp;
	t_cmds		*cmds;
	t_utils		*utils;

	tmp = tokens;
	*lst = NULL;
	if (!tokens)
		return (-1);
	if (init_struct_utils(&utils) == -1)
		return (-1);
	while (tmp)
	{
		cmds = malloc(sizeof(t_cmds));
		if (!cmds)
		{
			free_token_utils(utils, tokens);
			return (-1);
		}
		(utils)->sp_id = -1;
		init_struct_cmds(&cmds);
		tmp = fill_struct_cmds(cmds, tmp, utils);
		add_cmd_to_list(lst, cmds);
	}
	free_token_utils(utils, tokens);
	return (0);
}

int	fill_global_struct(t_global **global, char *line, int flag)
{
	t_tokens	*tokens;
	t_tokens	*updated_tokens;
	t_cmdshell	*lst_cmd;

	lst_cmd = NULL;
	if (split_and_fill_list(line, &tokens) == -1)
		return (-1);
	if (flag == 1)
		updated_tokens = analyzer(tokens, &(*global)->exit_status);
	else
		updated_tokens = tokens;
	if (fill_list_cmds(&lst_cmd, updated_tokens) == -1)
	{
		free_tokens(updated_tokens);
		return (-1);
	}
	(*global)->all_commands = lst_cmd;
	return (0);
}

// int	fill_global_struct(t_global **global, char *line)
// {
// 	t_tokens	*tokens;
// 	t_tokens	*updated_tokens;
// 	t_cmdshell	*lst_cmd;

// 	lst_cmd = NULL;
// 	if (split_and_fill_list(line, &tokens) == -1)
// 		return (-1);
// 	// if (!(*global)->all_commands)
// 		updated_tokens = analyzer(tokens, &(*global)->exit_status);
// 	// else
// 	// 	updated_tokens = tokens;
// 	if (fill_list_cmds(&lst_cmd, updated_tokens) == -1)
// 	{
// 		free_tokens(updated_tokens);
// 		return (-1);
// 	}
// 	(*global)->all_commands = lst_cmd;
// 	return (0);
// }

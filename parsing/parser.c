/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:33:58 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/30 11:59:41 by kchaouki         ###   ########.fr       */
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
	if (init_struct_utils(&utils) == -1)
		return (-1);
	if (!tokens)
		return (-1);
	while (tmp)
	{
		cmds = malloc(sizeof(t_cmds));
		if (!cmds)
		{
			//// free all
			return (-1);
		}
		utils->sp_id = -1;
		init_struct_cmds(&cmds);
		tmp = fill_struct_cmds(cmds, tmp, utils);
		add_cmd_to_list(lst, cmds);
		// free_redis(cmds->redis);
		// free_args(cmds->args);
		// free(cmds);
		// free(cmds->subshell);
	}
	free_tokens(tokens);
	free_double_ptr(utils->spl_sp_char);
	free_double_ptr(utils->spl_redi);
	free(utils);
	return (0);
}

int	fill_global_struct(t_global **global, char *line, char **environment)
{
	(void) environment;
	t_tokens	*tokens;
	t_tokens	*updated_tokens;
	t_cmdshell	*lst_cmd;

	lst_cmd = NULL;
	*global = malloc(sizeof(t_global));
	if (!(*global))
		return (-1);
	if (split_and_fill_list(line, &tokens) == -1)
		return (-1);
	(*global)->exit_status = 0;
	updated_tokens = analyzer(tokens, &(*global)->exit_status);
	if (fill_list_cmds(&lst_cmd, updated_tokens) == -1)
	{
		free_tokens(updated_tokens);
		return (-1);
	}
	(*global)->env = create_env(environment);
	(*global)->all_commands = lst_cmd;
	return (0);
}

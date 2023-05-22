/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/22 18:51:56 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdshell	*fill_list_cmds(t_cmdshell *lst, t_tokens *tokens)
{
	t_tokens	*tmp;
	t_cmds		*cmds;
	t_utils		*utils;

	tmp = tokens;
	lst = NULL;
	init_struct_utils(&utils);
	while (tmp)
	{
		cmds = malloc(sizeof(t_cmds));
		utils->sp_id = -1;
		init_struct_cmds(&cmds);
		tmp = fill_struct_cmds(cmds, tmp, utils);
		add_cmd_to_list(&lst, cmds);
		// free_redis(cmds->redis);
		// free_args(cmds->args);
		// free(cmds);
		// free(cmds->subshell);
	}
	free_tokens(tokens);
	free_double_ptr(utils->spl_sp_char);
	free_double_ptr(utils->spl_redi);
	free(utils);
	return (lst);
}

int	main(void)
{
	char	*read_line;
	t_tokens	*tokens;
	t_cmdshell *lst_cmd;
	// t_global	*glob;

	lst_cmd = NULL;
	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line)
		{
			if (read_line[0] != 0)
				add_history(read_line);
			tokens = split_and_fill_list(read_line);
			// while (tokens)
			// {
			// 	printf("%s\n", tokens->str);
			// 	tokens = tokens->next;
			// }
			// glob = malloc(sizeof(t_global));
			// if (!glob)
			// 	return (-1);
			lst_cmd = fill_list_cmds(lst_cmd, tokens);
			printf("\n--------------------------------------------------------------------------\n");
			while (lst_cmd)
			{
				printf("cmd ==> %s\n", lst_cmd->cmds->cmd);
				printf("subshell ===> %s\n", lst_cmd->cmds->subshell);
				printf("operator ===> %d\n", lst_cmd->cmds->operator);
				printf("\n=======  all arguments  =======\n");
				while(lst_cmd->cmds->args)
				{
					printf("arg : %s\n", lst_cmd->cmds->args->str);
					lst_cmd->cmds->args = lst_cmd->cmds->args->next;
				}
				printf("\n======= all redirections =======\n");
				while(lst_cmd->cmds->redis)
				{
					printf("red : %s\n", lst_cmd->cmds->redis->str);
					printf("type red : %d\n", lst_cmd->cmds->redis->type);
					printf("-----------------------------\n");
					lst_cmd->cmds->redis = lst_cmd->cmds->redis->next;
				}
				lst_cmd = lst_cmd->next;
				printf("\n---------------------------------END CMD-----------------------------------------\n");
			}
		}
		else
			break ;
	}
	printf("exit\n");
	return (0);
}

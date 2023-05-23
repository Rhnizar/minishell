/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/23 20:10:51 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_list_cmds(t_cmdshell **lst, t_tokens *tokens)
{
	t_tokens	*tmp;
	t_cmds		*cmds;
	t_utils		*utils;

	tmp = tokens;
	*lst = NULL;
	if (init_struct_utils(&utils) == -1)
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
	t_tokens	*tokens;
	t_tokens	*update_tokens;
	t_cmdshell *lst_cmd;
	t_env		*env;

	lst_cmd = NULL;
	*global = malloc(sizeof(t_global));
	if (!(*global))
		return (-1);
	if (split_and_fill_list(line, &tokens) == -1)
		return (-1);
	(*global)->exit_status = 0;
	update_tokens = analyzer(tokens, &(*global)->exit_status);
	// while(tmp_new_token)
	// {
	// 	printf("%s\n", tmp_new_token->str);
	// 	tmp_new_token = tmp_new_token->next;
	// }
	if (fill_list_cmds(&lst_cmd, update_tokens) == -1)
	{
		free_tokens(tokens);
		return (-1);
	}
	env = create_env(environment);
	(*global)->env = env;
	(*global)->all_commands = lst_cmd;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char		*line;
	t_global	*global;

	while (1)
	{
		line = readline("minishell ~ ");
		if (line)
		{
			if (line[0] != 0)
				add_history(line);
			else
				continue ;
			if (fill_global_struct(&global, line, env) == -1)
				return (-1);
			printf("\n--------------------------------------------------------------------------\n");
			while (global->all_commands)
			{
				printf("cmd ==> %s\n", global->all_commands->cmds->cmd);
				printf("subshell ===> %s\n", global->all_commands->cmds->subshell);
				printf("operator ===> %d\n", global->all_commands->cmds->operator);
				printf("\n=======  all arguments  =======\n");
				while(global->all_commands->cmds->args)
				{
					printf("arg : %s\n", global->all_commands->cmds->args->str);
					global->all_commands->cmds->args = global->all_commands->cmds->args->next;
				}
				printf("\n======= all redirections =======\n");
				while(global->all_commands->cmds->redis)
				{
					printf("red : %s\n", global->all_commands->cmds->redis->str);
					printf("type red : %d\n", global->all_commands->cmds->redis->type);
					printf("-----------------------------\n");
					global->all_commands->cmds->redis = global->all_commands->cmds->redis->next;
				}
				global->all_commands = global->all_commands->next;
				printf("\n---------------------------------END CMD-----------------------------------------\n");
			}
		}
		else
			break ;
	}
	printf("exit\n");
	return (0);
}

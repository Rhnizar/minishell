/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:09:32 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/22 23:33:44 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_bonus.h"

void	print_command(t_global	*global)
{
	while (global->all_commands)
	{
		printf("#######################################################################################################\n");
		printf("#     COMMAND NAME    #     ARGS    #     REDIRECTIONS    #		OPERATOR TYPE    #		SUBSHELL      #\n");
		printf("#######################################################################################################\n");
		printf("#%s					  #				#					  #	%d					 #%s				  #\n", global->all_commands->cmds->cmd, global->all_commands->cmds->operator, global->all_commands->cmds->subshell);
		while(global->all_commands->cmds->args)
		{
			printf("#					  #%s				#					  # 					 #  				  #\n", global->all_commands->cmds->args->str);
			global->all_commands->cmds->args = global->all_commands->cmds->args->next;
		}
		while(global->all_commands->cmds->redis)
		{
			printf("#					  #				#file: %s					  # 					 #  				  #\n", global->all_commands->cmds->redis->str);
			printf("#					  #				#type: %d					  # 					 #  				  #\n", global->all_commands->cmds->redis->type);
			global->all_commands->cmds->redis = global->all_commands->cmds->redis->next;
		}
		printf("#######################################################################################################\n");
		global->all_commands = global->all_commands->next;
	}
}
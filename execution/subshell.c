/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:42:07 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/13 22:06:41 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_parantheces(char *str)
{
	char	*output;
	int		count;
	int		i;
	int		j;

	i = 1;
	j = 0;
	count = ft_strlen(str);
	output = malloc(sizeof(char) * count - 1);
	if (!output)
		print_error(NULL, NULL, 1);
	while (i < count - 1)
		output[j++] = str[i++];
	output[j] = '\0';
	return (output);
}

void	run_subshell(t_global *global, char *subshell,int i ,int count)
{
	int		status;
	t_global	*new_global;

	status = 0;
	signal(SIGINT, SIG_IGN);
	global->pid[i] = fork();
	if (global->pid[i] == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
	else if (global->pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		read_write_pipe(global, i, count);
		init_global(&new_global, get_env(global->env));
		fill_global_struct(&new_global, remove_parantheces(subshell), 0);
		execution(new_global);
		exit(new_global->exit_status);
	}
}

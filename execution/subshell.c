/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:42:07 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/13 15:02:56 by rrhnizar         ###   ########.fr       */
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
	pid_t	pid;
	int		status;
	t_global	*new_global;

	status = 0;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		global_free(global);
		print_error(NULL, NULL, 1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (i < count - 1)
			fill_pipe(global, i, count);
		init_global(&new_global, get_env(global->env));
		fill_global_struct(&new_global, remove_parantheces(subshell), 0);
		execution(new_global);
		if (new_global->exit_status == 130)
			exit (2);
		else
			exit(new_global->exit_status);
	}
	waitpid(pid, &status, 0);
	if ((status >> 8) == 2)
		global->exit_status = 130;
	else
		global->exit_status = status >> 8;
	signal(SIGINT, sig_handl);
}


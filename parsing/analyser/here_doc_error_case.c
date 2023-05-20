/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_error_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:21:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/20 10:46:39 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	here_doc_error_case(char *delimiter)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid == -1)
		print_error(NULL, NULL, 1);
	if (pid == 0)
	{
		while (1)
		{
			line = readline("> ");
			if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
				break ;
			free(line);
		}
		free(line);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	run_here_docs(t_tokens	*here_docs)
{
	t_tokens	*tmp;

	if (here_docs)
	{
		tmp = here_docs;
		while (tmp)
		{
			here_doc_error_case(tmp->str);
			tmp = tmp->next;
		}
	}
	free_tokens(here_docs);
}
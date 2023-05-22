/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_error_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:21:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/17 17:57:16 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc_error_case(char *delimiter)
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

void	run_here_docs(char *str)
{
	char	**here_docs;
	int		i;

	if (str)
	{
		here_docs = ft_split(str, ' ');
		i = 0;
		while (here_docs[i])
			here_doc_error_case(here_docs[i++]);
		free_double_ptr(here_docs);
	}
}

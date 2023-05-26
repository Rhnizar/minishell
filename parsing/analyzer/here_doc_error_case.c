/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_error_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:21:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/26 13:00:16 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//need to add signal handler and remove fork

// int stop = 0;

// void	sig_hand_child(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		stop = 1;
// 		write(1, "\n", 1);
// 		// signal(SIGINT, sig_handl);
// 		// rl_on_new_line();
// 		// rl_replace_line("minishell ~ ", 0);
// 		// rl_redisplay();
// 	}
// }

static void	here_doc_error_case(char *delimiter)
{
	// pid_t	pid;
	char	*line;

	// pid = fork();
	// if (pid == -1)
	// 	print_error(NULL, NULL, 1);
	// if (pid == 0)
	// {
		line = NULL;
		while (1)
		{
			// signal(SIGINT, sig_hand_child);
			// if (stop == 1)
			// 	break;
			line = readline("> ");
			if (!line)
				break;
			if (ft_strcmp(line, delimiter) == 0)
				break ;
			free(line);
		}
		free(line);
	// }
	// waitpid(pid, NULL, 0);
}

static void	run_here_docs(t_tokens	*here_docs)
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

void	here_doc_befor_error(t_tokens *tokens, int index)
{
	t_tokens	*here_docs;
	t_tokens	*tmp;
	int			j;

	tmp = tokens;
	if (index == count_tokens(tokens))
		return ;
	here_docs = ((j = 0), NULL);
	while (tmp && j < index)
	{
		if (ft_strnstr(tmp->str, "<<", 2))
		{
			tmp = tmp->next;
			j++;
			create_tokens(&here_docs, ft_strdup(tmp->str));
		}
		j++;
		tmp = tmp->next;
	}
	run_here_docs(here_docs);
}

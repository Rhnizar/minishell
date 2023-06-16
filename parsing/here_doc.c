/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:35:00 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/16 00:34:25 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*herdoc_expander(t_global *global, char *line, char *delem)
{
	t_args	*arg;
	t_args	*new_arg;
	char	*output;

	arg = NULL;
	if (ft_strchr(delem, '"') || ft_strchr(delem, '\''))
		return (ft_strdup(line));
	else
	{
		fill_list_args(&arg, ft_strdup(line));
		new_arg = args_expander(global, arg);
	}
	output = ft_strdup(new_arg->str);
	free_args(new_arg);
	return (output);
}

static int	here_doc(t_global *global, char *delimiter)
{
	char	*line;
	int		fd[2];
	int		read_fd;
	char	*expanded_line;
	char	*delem;

	if (pipe(fd) == -1)
		return (print_error(NULL, NULL, -1), -1);
	read_fd = dup(fd[0]);
	if (close (fd[0]) == -1)
		return (print_error(NULL, NULL, -1), -1);
	expanded_line = NULL;
	delem = remove_quotes(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (-3);
		if (ft_strcmp(line, delem) == 0)
			break ;
		expanded_line = herdoc_expander(global, line, delimiter);
		ft_putstr_fd(expanded_line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(expanded_line);
		free(line);
	}
	free(delem);
	free(line);
	if (close (fd[1]) == -1)
		return (print_error(NULL, NULL, -1), -1);
	return (read_fd);
}

static int	get_last_heredoc(t_global *global, t_redis *redis)
{
	t_redis	*tmp;
	int		fd_new;
	int		fd_prev;

	fd_new = -2;
	fd_prev = -1;
	tmp = redis;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (fd_prev != -1 && close (fd_prev) == -1)
				return (print_error(NULL, NULL, -1), -1);
			fd_new = here_doc(global, tmp->str);
			fd_prev = fd_new;
			if (fd_new == -3)
				return (-3);
			if (fd_new == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (fd_new);
}

int	run_heredocs(t_global *global)
{
	t_cmdshell	*tmp;

	tmp = global->all_commands;
	while (tmp)
	{
		tmp->cmds->fd_herdoc = get_last_heredoc(global, tmp->cmds->redis);
		if (tmp->cmds->fd_herdoc == -3)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

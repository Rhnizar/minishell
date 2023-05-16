/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 09:36:17 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/16 22:40:15 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

static int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

char	**create_separator(void)
{
	if (BONUS == 0)
		return (ft_split(">> << > < |", ' '));
	return (ft_split(">> << > < || && | ( )", ' '));
}

static void	syntx_error(char *arg)
{
	ft_putstr_fd(ESYNTX, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\'\n", 2);
}

static char	*recognize_quote(int quote)
{
	if (quote == 1)
		return ("\'");
	return ("\"");
}

char	*find_separator(char **sep, char *str, int *sp)
{
	char	*output;
	int		j;

	j = 0;
	output = NULL;
	while (sep[j])
	{
		output = ft_strnstr(str, sep[j], ft_strlen(sep[j]));
		if (output != NULL)
			break ;
		j++;
	}
	if (*sp != -1)
		(*sp) = j;
	return (output);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	separator_checker(char **sep, char *arg, int sp_id, int *i)
{
	int		j;

	j = 0;
	j = skip_spaces(&arg[j]);
	if (sp_id < 4 || sp_id == 7)
	{
		j += arg_len(sep[sp_id]) + skip_spaces(&arg[j + arg_len(sep[sp_id])]);
		if (!arg[j])
			return (syntx_error("newline"), 1);
		find_separator(sep, &arg[j], &sp_id);
		if (sp_id < 9)
			return (syntx_error(sep[sp_id]), 1);
	}	
	else if (sp_id > 3 && sp_id != 7 && sp_id < 9)
	{
		if (j > 0 || *i == 0)
			return (syntx_error(sep[sp_id]), 1);
		j += arg_len(sep[sp_id]) + skip_spaces(&arg[j + arg_len(sep[sp_id])]);
		if (!arg[j])
			return (syntx_error("newline"), 1);
		find_separator(sep, &arg[j], &sp_id);
		if (sp_id > 3 && sp_id != 7 && sp_id < 9)
			return (syntx_error(sep[sp_id]), 1);
	}
	return (((*i) += j), 0);
}

int	skip_normale_characters(char **sep, char *str, int *sp_id)
{
	int		i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (is_quote(str[i]) || find_separator(sep , &str[i], sp_id))
		return (0);
	while (str[i] && !is_quote(str[i]) && !find_separator(sep , &str[i], sp_id))
		i++;
	return (i);	
}

int	find_snytx_error(char *arg)
{
	char	**sep;
	int		quote;
	int		sp_id;
	int		i;

	sp_id = ((i = 0), 0);
	sep = create_separator();
	while (arg[++i])
	{
		i += skip_normale_characters(sep, &arg[i], &sp_id);
		if (sp_id < 10 && separator_checker(sep, &arg[i], sp_id, &i))
			return (free_double_ptr(sep), i - 1);
		quote = is_quote(arg[i]);
		if (arg[i + 1] == '\0' && quote > 0)
			return (free_double_ptr(sep), syntx_error(recognize_quote(quote)), i - 1);
		else if (arg[i + 1] != '\0')
			i++;
		while (arg[i] && quote != is_quote(arg[i]))
			i++;
		if (arg[i] == '\0' && quote != is_quote(arg[i]))
			return (free_double_ptr(sep), syntx_error(recognize_quote(quote)), i - 1);
	}
	return (i - 1);
}

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

	here_docs = ft_split(str, ' ');
	i = 0;
	while (here_docs[i])
		here_doc_error_case(here_docs[i++]);
	free_double_ptr(here_docs);
}

char	*get_exact_arg(char *str)
{
	char	*output;
	char	**sep;
	int		sp_id;
	int		i;

	i = 0;
	sp_id = -1;
	output = NULL;
	sep = create_separator();
	i += 2;
	i += skip_spaces(&str[i]);
	while (str[i] && str[i] != ' ' && str[i] != '\t' 
	&& !find_separator(sep, &str[i], &sp_id))
		output = join_to_str(output, str[i++]);
	return (output);
}

char	*join_with_space(char *old, char *arg)
{
	char	*output;
	int		i;
	int		j;

	output = malloc(arg_len(old) + arg_len(arg) + 2);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (old && old[j])
		output[i++] = old[j++];
	if (old)
		output[i++] = ' ';
	j = 0;
	while (arg && arg[j])
		output[i++] = arg[j++];
	output[i] = '\0';
	if (old)
		free(old);
	return (output);
}

int	syntax_error_handler(char *arg)
{
	int		error_index;
	char	*here_docs;
	char	*exact_arg;
	char	*ret;
	int		j;

	error_index = find_snytx_error(arg);
	if (arg_len(arg) == error_index)
		return (0);
	j = 0;
	here_docs = NULL;
	while (j < error_index)
	{
		ret = ft_strnstr(&arg[j], "<<", error_index);
		if (!ret)
			break ;
		j += arg_len(&arg[j]) - arg_len(ret) - 1;
		exact_arg = get_exact_arg(ret);
		here_docs = join_with_space(here_docs, exact_arg);
		j += arg_len(exact_arg);
	}
	run_here_docs(here_docs);
	free(here_docs);
	return (258);
}
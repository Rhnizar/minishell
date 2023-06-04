/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:39:59 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/04 14:25:17 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_global(t_global **global, char **env)
{
	*global = malloc(sizeof(t_global));
	if (!*global)
		exit (-1);
	(*global)->exit_status = 0;
	(*global)->env = create_env(env);
	// (void)env;
	// (*global)->env = NULL;
	(*global)->export = _export((*global)->env);
	// (*global)->export = NULL;
	return (0);
}

char	*join_to_str(char *str, char c)
{
	char	*output;
	int		i;

	if (!str)
		output = malloc(2);
	else
		output = malloc(ft_strlen(str) + 2);
	if (!output)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i++] = c;
	output[i] = '\0';
	free (str);
	return (output);
}

void	print_error(char *msg, char *arg, int status)
{
	char	*error_msg;

	if (msg && !arg)
		ft_putstr_fd(msg, 2);
	else if (!msg && !arg)
	{
		error_msg = ft_strjoin(ft_strdup("minishell: "), strerror(errno));
		ft_putstr_fd(error_msg, 2);
		ft_putchar_fd('\n', 2);
		free (error_msg);
	}
	else
	{
		arg = ft_strjoin(ft_strdup("minishell: "), arg);
		error_msg = ft_strjoin(arg, msg);
		ft_putstr_fd(error_msg, 2);
		free (error_msg);
	}
	if (status != -1)
		exit(status);
}

int	count_split(char **split)
{
	int	count;

	count = 0;
	while (split && split[count])
		count++;
	return (count);
}

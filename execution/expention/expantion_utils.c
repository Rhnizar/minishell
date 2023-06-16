/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:16:04 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/16 00:38:09 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_non_alnum(char	*output, t_tokens **tmp, int exit_status)
{
	char	*status;

	if (!ft_strcmp((*tmp)->str, "\"") || !ft_strcmp((*tmp)->str, "'"))
		(*tmp) = (*tmp)->prev;
	else if (!ft_strcmp((*tmp)->str, "?"))
	{
		status = ft_itoa(exit_status);
		output = ft_strjoin(output, status);
		free (status);
	}
	else
	{
		output = ft_strjoin(output, (*tmp)->prev->str);
		output = ft_strjoin(output, (*tmp)->str);
	}
	return (output);
}

char	*handle_alnum(t_env *env, char *output, char *old, char *str)
{
	char	*value;

	if (ft_isdigit(str[0]))
			output = ft_strjoin(output, &str[1]);
	else
	{
		value = get_value(str, env);
		if (!value && !old)
			return (NULL);
		output = ft_strjoin(output, value);
		free(value);
	}
	return (output);
}

char	*expantion_dollar_case(t_tokens **tmp, t_env *env, \
char *old, int exit_status)
{
	char	*output;
	char	*new;
	int		count_dollar;

	output = ((count_dollar = 0), NULL);
	if (skipp_dollar(tmp, &count_dollar, &output))
	{
		if (!old)
			return (output);
		return (ft_strjoin(old, output));
	}
	if (!ft_isalnum((*tmp)->str[0]) && (*tmp)->str[0] != '_')
		output = handle_non_alnum(output, tmp, exit_status);
	else if ((ft_isalnum((*tmp)->str[0]) || (*tmp)->str[0] =='_') && count_dollar % 2 != 0)
		output = handle_alnum(env, output, old, (*tmp)->str);
	else
		output = ft_strjoin(output, (*tmp)->str);
	new = ft_strjoin(old, output);
	return (free(output), new);
}

static char	*double_quote_case(t_tokens **tmp, t_env *env, int exit_status)
{
	char	*output;

	output = NULL;
	output = ft_strjoin(output, (*tmp)->str);
	(*tmp) = (*tmp)->next;
	while ((*tmp) && ft_strcmp((*tmp)->str, "\""))
	{
		if (!ft_strcmp((*tmp)->str, "$"))
		{
			output = expantion_dollar_case(tmp, env, output, exit_status);
			if (!(*tmp) || !ft_strcmp((*tmp)->str, "\""))
				break ;
		}
		else
			output = ft_strjoin(output, (*tmp)->str);
		(*tmp) = (*tmp)->next;
	}
	output = ft_strjoin(output, (*tmp)->str);
	return (output);
}

char	*expantion_quote_case(t_tokens **tmp, t_env *env, \
char *old, int exit_status)
{
	char	*output;

	output = NULL;
	if (!ft_strcmp((*tmp)->str, "'"))
	{
		output = ft_strjoin(output, (*tmp)->str);
		(*tmp) = (*tmp)->next;
		while ((*tmp) && ft_strcmp((*tmp)->str, "'"))
		{
			output = ft_strjoin(output, (*tmp)->str);
			if (!(*tmp)->next)
				break ;
			(*tmp) = (*tmp)->next;
		}
		output = ft_strjoin(output, (*tmp)->str);
	}
	if (!ft_strcmp((*tmp)->str, "\""))
		output = double_quote_case(tmp, env, exit_status);
	return (ft_strjoin(old, output));
}

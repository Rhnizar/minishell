/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:16:04 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/19 17:39:35 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_non_alnum(char	*output, t_tokens **tmp, int exit_status)
{
	char	*status;

	if ((*tmp) && (!ft_strcmp((*tmp)->str, "\"") \
	|| !ft_strcmp((*tmp)->str, "'")))
		(*tmp) = (*tmp)->prev;
	else if ((*tmp) && !ft_strcmp((*tmp)->str, "?"))
	{
		status = ft_itoa(exit_status);
		output = ft_strjoin(output, status);
		free (status);
	}
	else if ((*tmp) && !ft_strcmp((*tmp)->str, "@"))
		return (output);
	else
	{
		output = ft_strjoin(output, (*tmp)->prev->str);
		output = ft_strjoin(output, (*tmp)->str);
	}
	return (output);
}

static char	*handle_alnum(t_env *env, char *output, char *str, int flag)
{
	char	*value;

	if (ft_isdigit(str[0]))
			output = ft_strjoin(output, &str[1]);
	else
	{
		value = get_value(str, env);
		if (!value)
			return (NULL);
		if (flag)
			value = add_nonprintable(value);
		output = ft_strjoin(output, value);
		free(value);
	}
	return (output);
}

char	*expantion_dollar_case(t_global *global, t_tokens **tmp, \
char *old, int flag)
{
	char	*output;
	char	*new;
	int		count_dollar;

	output = ((count_dollar = 0), NULL);
	if (skipp_dollar(tmp, &count_dollar, &output))
	{
		if (!old)
			return (output);
		new = ft_strjoin(old, output);
		return (free (output), new);
	}
	if (!ft_isalnum((*tmp)->str[0]) && (*tmp)->str[0] != '_')
		output = handle_non_alnum(output, tmp, global->exit_status);
	else if ((ft_isalnum((*tmp)->str[0]) || \
	(*tmp)->str[0] == '_') && count_dollar % 2 != 0)
		output = handle_alnum(global->env, output, (*tmp)->str, flag);
	else
		output = ft_strjoin(output, (*tmp)->str);
	new = ft_strjoin(old, output);
	return (free(output), new);
}

static char	*double_quote_case(t_global *global, t_tokens **tmp, int flag)
{
	char	*output;

	output = NULL;
	output = ft_strjoin(output, (*tmp)->str);
	(*tmp) = (*tmp)->next;
	while ((*tmp) && ft_strcmp((*tmp)->str, "\""))
	{
		if (!ft_strcmp((*tmp)->str, "$"))
		{
			output = expantion_dollar_case(global, tmp, output, flag);
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

char	*expantion_quote_case(t_global *global, t_tokens **tmp, \
char *old, int flag)
{
	char	*output;
	char	*new;

	output = NULL;
	if ((*tmp) && !ft_strcmp((*tmp)->str, "'"))
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
	if ((*tmp) && !ft_strcmp((*tmp)->str, "\""))
		output = double_quote_case(global, tmp, flag);
	new = ft_strjoin(old, output);
	return (free (output), new);
}

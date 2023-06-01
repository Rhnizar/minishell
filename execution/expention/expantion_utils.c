/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:16:04 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/01 11:40:16 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_quotes(char *str)
{
	char	*output;
	char	*quote;
	int		i;

	i = -1;
	quote = NULL;
	output = NULL;
	while (str[++i])
	{
		while (str[i] && !ft_strchr("\"'", str[i]))
			output = join_to_str(output, str[i++]);
		if (!str[i])
			break ;
		quote = ft_strchr("\"'", str[i]);
		if (str[i + 1])
			i++;
		while (str[i] && quote[0] != str[i])
			output = join_to_str(output, str[i++]);
	}
	return (output);
}

char	*get_value(char *to_expand, t_env *env)
{
	char	*output;
	t_env	*tmp;

	output = NULL;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, to_expand))
		{
			output = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (output);
}

char	*expantion_dollar_case(t_tokens **tmp, t_env *env, char *old)
{
	char	*output;
	char	*value;

	output = NULL;
	if (!(*tmp)->next)
		output = ft_strjoin(output, (*tmp)->str);
	else if (ft_strcmp((*tmp)->next->str, "$") \
	&& ft_strcmp((*tmp)->next->str, "'") \
	&& ft_strcmp((*tmp)->next->str, "\""))
	{
		(*tmp) = (*tmp)->next;
		value = get_value((*tmp)->str, env);
		if (ft_strlen(value) == 0 && !old)
			return (NULL);
		output = ft_strjoin(output, value);
		free(value);
	}
	return (ft_strjoin(old, output));
}

static char	*double_quote_case(t_tokens **tmp, t_env *env)
{
	char	*output;
	char	*value;

	output = NULL;
	output = ft_strjoin(output, (*tmp)->str);
	(*tmp) = (*tmp)->next;
	while ((*tmp) && ft_strcmp((*tmp)->str, "\""))
	{
		if (!ft_strcmp((*tmp)->str, "$"))
		{
			(*tmp) = (*tmp)->next;
			value = get_value((*tmp)->str, env);
			output = ft_strjoin(output, value);
			free (value);
		}
		else
			output = ft_strjoin(output, (*tmp)->str);
		(*tmp) = (*tmp)->next;
	}
	output = ft_strjoin(output, (*tmp)->str);
	return (output);
}

char	*expantion_quote_case(t_tokens **tmp, t_env *env, char *old)
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
			(*tmp) = (*tmp)->next;
		}
		output = ft_strjoin(output, (*tmp)->str);
	}
	if (!ft_strcmp((*tmp)->str, "\""))
		output = double_quote_case(tmp, env);
	return (ft_strjoin(old, output));
}

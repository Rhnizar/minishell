/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:16:04 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/31 20:17:53 by kchaouki         ###   ########.fr       */
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

t_tokens	*expantion_tokenizer(char *token)
{
	t_tokens	*tokens;
	char		**output;
	char		*to_split;
	int			i;
	
	to_split = ((i = 0), NULL);
	while (token[i])
	{
		if (ft_strchr("\"'$", token[i]))
		{
			to_split = join_to_str(to_split, '\x07');
			to_split = join_to_str(to_split, token[i]);
			to_split = join_to_str(to_split, '\x07');
		}
		else
			to_split = join_to_str(to_split, token[i]);
		i++;			
	}
	i = 0;
	tokens = NULL;
	output = ft_split(to_split, '\x07');
	while (output[i])
		create_tokens(&tokens, ft_strdup(output[i++]));
	return (free(to_split), free_double_ptr(output), tokens);
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

static char	*double_quote_case(t_tokens **tmp, t_env *env)
{
	char	*output;

	output = NULL;
	while ((*tmp) && ft_strcmp((*tmp)->str, "\""))
	{
		if (!ft_strcmp((*tmp)->str, "$"))
		{
			(*tmp) = (*tmp)->next;
			output = ft_strjoin(output, get_value((*tmp)->str, env));
		}
		else
			output = ft_strjoin(output, (*tmp)->str);
		(*tmp) = (*tmp)->next;
	}
	return (output);
}

char	*expantion_quote_case(t_tokens **tmp, t_env *env, char *old)
{
	char	*output;

	output = NULL;
	if (!ft_strcmp((*tmp)->str, "'"))
	{
		(*tmp) = (*tmp)->next;
		while ((*tmp) && ft_strcmp((*tmp)->str, "'"))
		{
			output = ft_strjoin(output, (*tmp)->str);
			(*tmp) = (*tmp)->next;
		}
	}
	if (!ft_strcmp((*tmp)->str, "\""))
	{
		(*tmp) = (*tmp)->next;
		output = double_quote_case(tmp, env);
	}
	return (ft_strjoin(old, output));
}

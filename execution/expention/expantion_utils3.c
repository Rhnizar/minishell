/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 07:50:54 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/17 17:51:13 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skipp_dollar(t_tokens **tmp, int *count_dollar, char **output)
{
	t_tokens	*tmp2;
	t_tokens	*tmp3;

	tmp3 = NULL;
	if ((*tmp)->prev)
		tmp3 = (*tmp)->prev;
	while ((*tmp) && !ft_strcmp((*tmp)->str, "$"))
	{
		(*count_dollar)++;
		tmp2 = (*tmp);
		(*tmp) = (*tmp)->next;
	}
	if (!(*tmp))
	{
		if ((*count_dollar) % 2 != 0 && !ft_strcmp(tmp2->str, "$"))
			(*output) = ft_strjoin((*output), tmp2->str);
		return (1);
	}
	if ((*tmp) && !ft_strcmp((*tmp)->str, "\"") && \
		tmp3 && !ft_strcmp(tmp3->str, "\""))
		if ((*count_dollar) % 2 != 0 && !ft_strcmp(tmp2->str, "$"))
			(*output) = ft_strjoin((*output), tmp2->str);
	return (0);
}

t_tokens	*expantion_tokenizer(char *token)
{
	t_tokens	*tokens;
	char		**output;
	char		*to_split;
	int			i;

	to_split = ((i = 0), NULL);
	while (token && token[i])
	{
		if (!ft_isalnum(token[i]) && token[i] != '_')
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
	while (output && output[i])
		create_tokens(&tokens, ft_strdup(output[i++]));
	return (free(to_split), free_double_ptr(output), tokens);
}

int	count_split(char **split)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (split && split[i])
	{
		if ((split[i][0] == '\'' && split[i][1] == '\'' \
			&& split[i][2] == '\0') || \
			(split[i][0] == '\"' && split[i][1] == '\"' \
			&& split[i][2] == '\0'))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	is_wildcard(char *str)
{
	char	*quote;
	int		i;

	i = -1;
	quote = NULL;
	while (str && str[++i])
	{
		while (str[i] && !ft_strchr("\"'", str[i]))
		{
			if (str[i] == '*')
				return (1);
			i++;
		}
		if (!str[i])
			break ;
		quote = ft_strchr("\"'", str[i]);
		if (str[i + 1])
			i++;
		while (str[i] && quote[0] != str[i])
			i++;
	}
	return (0);
}

t_tokens	*expention_wildcard_case(char *to_handle)
{
	t_tokens	*tokens;

	if (is_wildcard(to_handle))
		return (wildcard(to_handle));
	create_tokens(&tokens, ft_strdup(to_handle));
	return (tokens);
}

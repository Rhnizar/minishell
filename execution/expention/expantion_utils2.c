/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:30:45 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/12 23:50:31 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (!output)
		return (ft_strdup(""));
	return (output);
}

static int	split_quote_case(char *token, int *j, char	**to_split)
{
	int	i;

	i = 0;
	(*to_split) = join_to_str((*to_split), token[i++]);
	while (token[i] && !ft_strchr("\"'", token[i]))
		(*to_split) = join_to_str((*to_split), token[i++]);
	if (!token[i])
		return (1);
	(*to_split) = join_to_str((*to_split), token[i]);
	(*j) += i;
	return (0);
}

int	implant_nonprint(char **to_split, char *token, int *j)
{
	int	i;

	i = 0;
	if (ft_strchr(" \t", token[i]))
	{
		while (token[i] && ft_strchr(" \t", token[i]))
			i++;
		if (!token[i])
			return (1);
		(*to_split) = join_to_str((*to_split), '\x07');
		(*to_split) = join_to_str((*to_split), token[i]);
	}
	else if (ft_strchr("\"'", token[i]))
	{
		if (split_quote_case(&token[i], &i, to_split))
			return (1);
	}
	else
		(*to_split) = join_to_str((*to_split), token[i]);
	*j += i;
	return (0);
}

char	**split_expended(char *token)
{
	char	*to_split;
	char	**split;
	int		i;

	to_split = NULL;
	split = NULL;
	i = 0;
	while (token && token[i])
	{
		if (implant_nonprint(&to_split, &token[i], &i))
			break ;
		i++;
	}
	if (to_split)
		split = ft_split(to_split, '\x07');
	return (free(to_split), split);
}

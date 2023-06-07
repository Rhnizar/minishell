/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:30:45 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/07 15:37:16 by rrhnizar         ###   ########.fr       */
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

char	**split_expended(char *token)
{
	char	*to_split;
	char	**split;
	int		i;

	to_split = ((i = 0), NULL);
	while (token[i])
	{
		if (ft_strchr(" \t", token[i]))
		{
			while (token[i] && ft_strchr(" \t", token[i]))
				i++;
			if (!token[i])
				break ;
			to_split = join_to_str(to_split, '\x07');
			to_split = join_to_str(to_split, token[i]);
		}
		else if (ft_strchr("\"'", token[i]))
		{
			if (split_quote_case(&token[i], &i, &to_split))
				break ;
		}
		else
			to_split = join_to_str(to_split, token[i]);
		i++;
	}
	split = ft_split(to_split, '\x07');
	return (free(to_split), split);
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
	while (output[i])
		create_tokens(&tokens, ft_strdup(output[i++]));
	return (free(to_split), free_double_ptr(output), tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:30:45 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/01 11:40:08 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_split(char **split)
{
	int	count;

	count = 0;
	while (split && split[count])
		count++;
	return (count);
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
	return (ft_split(to_split, '\x07'));
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

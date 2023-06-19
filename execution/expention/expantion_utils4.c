/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:07:55 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/19 17:00:56 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_space_only(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = remove_quotes(str);
	while (new && new[i] == '\x07')
		i++;
	if (new && i > 0 && new[i] == 0)
		return (free(new), 1);
	return (free(new), 0);
}

int	expanded_into_redis(t_global *global, t_redis **redis, t_redis *old_redis)
{
	t_tokens	*tokens;
	t_tokens	*tmp;
	char		*output;

	tokens = expantion_tokenizer(old_redis->str);
	output = ((tmp = tokens), NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->str, "$"))
		{
			output = expantion_dollar_case(global, &tmp, output, 1);
			if (!tmp)
				break ;
		}
		else if (!ft_strcmp(tmp->str, "'") || !ft_strcmp(tmp->str, "\""))
			output = expantion_quote_case(global, &tmp, output, 0);
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	if (add_expanded_to_redis(redis, output, old_redis->str, old_redis->type))
		return (free_tokens(tokens), free(output), 1);
	return (free_tokens(tokens), free(output), 0);
}

static void	lkmala(t_global *global, t_tokens **tmp, char **output)
{
	*output = join_to_str(*output, '\x01');
	*output = expantion_dollar_case(global, tmp, *output, 1);
	*output = join_to_str(*output, '\x01');
}

void	expanded_into_args(t_args **args, char *token, t_global *global)
{
	t_tokens	*tokens;
	t_tokens	*tmp;
	char		*output;

	tokens = expantion_tokenizer(token);
	output = ((tmp = tokens), NULL);
	while (tmp)
	{
		if (!ft_strcmp(tmp->str, "$"))
		{
			lkmala(global, &tmp, &output);
			if (!tmp)
				break ;
		}
		else if (!ft_strcmp(tmp->str, "'") || !ft_strcmp(tmp->str, "\""))
			output = expantion_quote_case(global, &tmp, output, 0);
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	free_tokens(tokens);
	add_expanded_to_args(args, output);
	free(output);
}

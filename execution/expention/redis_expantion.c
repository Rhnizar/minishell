/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redis_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:13:15 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/03 12:57:20 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	add_expanded_to_redis(t_redis **redis, char *expended, char *token, int type)
{
	char		**split;
	int			i;

	i = 0;
	if (!expended && (type == 0 || type == 3))
	{
		print_error(EAMBGRD, token, -1);
		return (1);
	}
	split = split_expended(expended);
	if (count_split(split) > 1 && (type == 0 || type == 3))
	{
		print_error(EAMBGRD, token, -1);
		free_double_ptr(split);
		return (1);
	}
	while (split[i])
		fill_list_redis(redis, remove_quotes(split[i++]), type);
	free_double_ptr(split);
	return (0);
}

static int	expanded_into_redis(t_redis **redis, t_redis *old_redis, t_env *env, int exit_status)
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
			output = expantion_dollar_case(&tmp, env, output, exit_status);
			if (!tmp->next)
				break ;
		}
		else if (!ft_strcmp(tmp->str, "'") || !ft_strcmp(tmp->str, "\""))
			output = expantion_quote_case(&tmp, env, output);
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	if(add_expanded_to_redis(redis, output, old_redis->str, old_redis->type))
		return (1);
	return (free_tokens(tokens), free(output), 0);
}

t_redis	*redis_expander(t_redis *redis, t_env *env, int exit_status)
{
	t_redis		*new_redis;

	new_redis = NULL;
	if (redis && ft_strchr(redis->str, '$') && redis->type != 1)
	{
		if (expanded_into_redis(&new_redis, redis, env, exit_status))
			return (NULL);
	}
	return (new_redis);
}

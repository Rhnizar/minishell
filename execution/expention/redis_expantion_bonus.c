/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redis_expantion_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:13:15 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/16 11:19:32 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	wildcard_into_redis(t_redis **redis, char *to_handle, int type)
{
	t_tokens	*tokens;

	tokens = expention_wildcard_case(to_handle);
	if (count_tokens(tokens) > 1)
	{
		print_error(EAMBGRD, to_handle, -1);
		return (free_tokens(tokens), 1);
	}
	fill_list_redis(redis, ft_strdup(tokens->str), type);
	free_tokens(tokens);
	return (0);
}

int	add_expanded_to_redis(t_redis **redis, char *expended, \
char *token, int type)
{
	char		**split;

	if ((expended == NULL || expended[0] == '\0') && type <= 3 && type != 1)
	{
		print_error(EAMBGRD, token, -1);
		return (1);
	}
	split = split_expended(expended);
	if (type <= 3 && type != 1 && count_split(split) > 1)
	{
		print_error(EAMBGRD, token, -1);
		return (free_double_ptr(split), 1);
	}
	if (split && ft_strchr(split[0], '*'))
	{
		if (wildcard_into_redis(redis, split[0], type))
			return (free_double_ptr(split), 1);
	}
	else
		fill_list_redis(redis, ft_strdup(split[0]), type);
	return (free_double_ptr(split), 0);
}

t_redis	*redis_expander(t_global *global, t_redis *redis)
{
	t_redis		*new_redis;

	new_redis = NULL;
	if (redis && (ft_strchr(redis->str, '$') \
	|| ft_strchr(redis->str, '*')) && redis->type != 1)
	{
		if (expanded_into_redis(&new_redis, redis, \
		global->env, global->exit_status))
			return (NULL);
	}
	else if (redis)
		fill_list_redis(&new_redis, remove_quotes(redis->str), redis->type);
	return (new_redis);
}

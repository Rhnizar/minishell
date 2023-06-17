/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redis_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:13:15 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/17 01:16:35 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	add_expanded_to_redis(t_redis **redis, char *expended, \
char *token, int type)
{
	char		**split;

	if ((expended == NULL || expended[0] == '\0' || has_space_only(expended)))
	{
		print_error(EAMBGRD, token, -1);
		return (1);
	}
	split = split_expended(expended);
	if (count_split(split) > 1)
	{
		print_error(EAMBGRD, token, -1);
		return (free_double_ptr(split), 1);
	}
	else if (split)
		fill_list_redis(redis, redis_value(split), type);
	return (free_double_ptr(split), 0);
}

t_redis	*redis_expander(t_global *global, t_redis *redis)
{
	t_redis		*new_redis;

	new_redis = NULL;
	if (redis && ft_strchr(redis->str, '$') && redis->type != 1)
	{
		if (expanded_into_redis(&new_redis, redis, \
		global->env, global->exit_status))
			return (NULL);
	}
	else if (redis)
		fill_list_redis(&new_redis, remove_quotes(redis->str), redis->type);
	return (new_redis);
}

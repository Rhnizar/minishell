/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redis_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:13:15 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/31 20:28:01 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_redis	*args_expander(t_redis *redis, t_env *env)
{
	t_redis		*tmp;
	t_redis		*new_args;

	new_args = NULL;
	tmp = redis;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '$'))
			expanded_into_args(&new_args, tmp->str, env);
		else
			fill_list_redis(&new_args, remove_quotes(tmp->str), tmp->type);
		tmp = tmp->next;
	}
	free_redis(redis);
	return (new_args);
}

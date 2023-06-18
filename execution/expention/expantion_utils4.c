/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:07:55 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/18 13:09:47 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	has_space_only(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = remove_quotes(str);
	while (new && (new[i] == ' ' || new[i] == '\t'))
		i++;
	if (new && i > 0 && new[i] == 0)
		return (free(new), 1);
	return (free(new), 0);
}

char	*redis_value(char **split)
{
	char		*output;
	char		*final_output;
	int			i;

	output = NULL;
	i = 0;
	while (split[i])
		output = ft_strjoin(output, split[i++]);
	final_output = remove_quotes(output);
	free(output);
	return (final_output);
}

int	expanded_into_redis(t_redis **redis, t_redis *old_redis, \
t_env *env, int exit_status)
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
			if (!tmp)
				break ;
		}
		else if (!ft_strcmp(tmp->str, "'") || !ft_strcmp(tmp->str, "\""))
			output = expantion_quote_case(&tmp, env, output, exit_status);
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
	*output = expantion_dollar_case(tmp, global->env, \
	*output, global->exit_status);
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
			output = expantion_quote_case(&tmp, global->env, output, \
			global->exit_status);
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	free_tokens(tokens);
	add_expanded_to_args(args, output);
	free(output);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_expantion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:02:54 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/31 20:21:21 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_expanded_to_args(t_args **args, char *expended)
{
	char		**split;
	int			i;

	i = 0;
	if (!expended)
		return ;
	split = ft_split(expended, ' ');
	while (split[i])
		fill_list_args(args, ft_strdup(split[i++]));
	free_double_ptr(split);
}

static char	*expantion_dollar_case(t_tokens **tmp, t_env *env, char *old)
{
	char	*output;

	output = NULL;
	if (!(*tmp)->next)
		output = ft_strjoin(output, (*tmp)->str);
	else if (ft_strcmp((*tmp)->next->str, "$") \
	&& ft_strcmp((*tmp)->next->str, "'") \
	&& ft_strcmp((*tmp)->next->str, "\""))
	{
		(*tmp) = (*tmp)->next;
		output = ft_strjoin(output, get_value((*tmp)->str, env));
	}
	return (ft_strjoin(old, output));
}

static void	expanded_into_args(t_args **args, char *token, t_env *env)
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
			output = expantion_dollar_case(&tmp, env, output);
			if (!tmp->next)
				break ;
		}
		else if (!ft_strcmp(tmp->str, "'") || !ft_strcmp(tmp->str, "\""))
			output = expantion_quote_case(&tmp, env, output);
		else
			output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
	}
	add_expanded_to_args(args, output);
	free_tokens(tokens);
	free(output);
}

t_args	*args_expander(t_args *args, t_env *env)
{
	t_args		*tmp;
	t_args		*new_args;

	new_args = NULL;
	tmp = args;
	while (tmp)
	{
		if (ft_strchr(tmp->str, '$'))
			expanded_into_args(&new_args, tmp->str, env);
		else
			fill_list_args(&new_args, remove_quotes(tmp->str));
		tmp = tmp->next;
	}
	free_args(args);
	return (new_args);
}

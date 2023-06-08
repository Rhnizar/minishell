/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_expantion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:02:54 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/08 10:25:25 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// static void	wildcard_into_args(t_args **args, char *to_handle)
// {
// 	t_tokens	*tokens;
// 	t_tokens	*tmp;

// 	tokens = expention_wildcard_case(to_handle);
// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		fill_list_args(args, remove_quotes(tmp->str));
// 		tmp = tmp->next;
// 	}
// 	free_tokens(tokens);
// }

static void	add_expanded_to_args(t_args **args, char *expended)
{
	char		**split;
	int			i;

	if (!expended)
		return ;
	split = split_expended(expended);
	i = 0;
	while (split[i])
	{
		// if (ft_strchr(split[i], '*'))
		// 	wildcard_into_args(args, split[i]);
		// else
		fill_list_args(args, remove_quotes(split[i]));
		i++;
	}
	free_double_ptr(split);
}

static void	expanded_into_args(t_args **args, char *token, t_global *global)
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
			output = expantion_dollar_case(&tmp, global->env, \
			output, global->exit_status);
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

t_args	*args_expander(t_global *global, t_args	*args)
{
	t_args		*tmp;
	t_args		*new_args;

	new_args = NULL;
	tmp = args;
	while (tmp)
	{
		if ((ft_strchr(tmp->str, '$') || ft_strchr(tmp->str, '*')))
			expanded_into_args(&new_args, tmp->str, global);
		else
			fill_list_args(&new_args, remove_quotes(tmp->str));
		tmp = tmp->next;
	}
	return (new_args);
}

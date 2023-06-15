/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_expantion_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:16:37 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/15 10:23:29 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	wildcard_into_args(t_args **args, char *to_handle)
{
	t_tokens	*tokens;
	t_tokens	*tmp;

	tmp = NULL;
	tokens = expention_wildcard_case(to_handle);
	if (!tokens)
	{
		fill_list_args(args, remove_quotes(to_handle));
		return ;
	}
	tmp = tokens;
	while (tmp)
	{
		fill_list_args(args, ft_strdup(tmp->str));
		tmp = tmp->next;
	}
	free_tokens(tokens);
}

void	add_expanded_to_args(t_args **args, char *expended)
{
	char		**split;
	int			i;

	if (!expended)
		return ;
	split = split_expended(expended);
	i = 0;
	while (split && split[i])
	{
		if (ft_strchr(split[i], '*'))
			wildcard_into_args(args, split[i]);
		else
			fill_list_args(args, remove_quotes(split[i]));
		i++;
	}
	if (split)
		free_double_ptr(split);
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
	free_args(args);
	return (new_args);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_expantion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:02:54 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/17 11:19:29 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_nonprint(char *str)
{
	char	*output;
	int		i;

	i = 0;
	output = NULL;
	while (str[i])
	{
		if (str[i] != '\x01')
			output = join_to_str(output, str[i]);
		if (str[i])
		i++;
	}
	return (output);
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
		if (ft_strchr(split[i], '\x01'))
			fill_list_args(args, remove_nonprint(split[i]));
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
		if ((ft_strchr(tmp->str, '$')))
			expanded_into_args(&new_args, tmp->str, global);
		else
			fill_list_args(&new_args, remove_quotes(tmp->str));
		tmp = tmp->next;
	}
	free_args(args);
	return (new_args);
}

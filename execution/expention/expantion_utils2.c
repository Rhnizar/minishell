/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 11:30:45 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/19 17:40:05 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value(char *to_expand, t_env *env)
{
	char	*output;
	t_env	*tmp;

	output = NULL;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var, to_expand))
		{
			output = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (output);
}

char	*remove_quotes(char *str)
{
	char	*output;
	char	*quote;
	int		i;

	i = -1;
	quote = NULL;
	output = NULL;
	while (str && str[++i])
	{
		while (str[i] && !ft_strchr("\"'", str[i]))
			output = join_to_str(output, str[i++]);
		if (!str[i])
			break ;
		quote = ft_strchr("\"'", str[i]);
		if (str[i + 1])
			i++;
		while (str[i] && quote[0] != str[i])
			output = join_to_str(output, str[i++]);
	}
	if (!output)
		return (ft_strdup(""));
	return (output);
}

char	**prepare_to_fill(t_redis **redis, int type, char *expended)
{
	char		**split;
	char		*new_expended;

	split = NULL;
	new_expended = filter_expanded(expended, -1);
	new_expended = remove_nonprint(new_expended);
	if (new_expended)
		split = ft_split(new_expended, '\x07');
	else
		fill_list_redis(redis, ft_strdup(""), type);
	return (free(new_expended), split);
}

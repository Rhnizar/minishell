/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 07:50:54 by kchaouki          #+#    #+#             */
/*   Updated: 2023/06/07 08:57:59 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_split(char **split)
{
	int	count;

	count = 0;
	while (split && split[count])
		count++;
	return (count);
}

int	is_wildcard(char *str)
{
	char	*quote;
	int		i;

	i = -1;
	quote = NULL;
	while (str[++i])
	{
		while (str[i] && !ft_strchr("\"'", str[i]))
		{
			if (str[i] == '*')
				return (1);
			i++;
		}
		if (!str[i])
			break ;
		quote = ft_strchr("\"'", str[i]);
		if (str[i + 1])
			i++;
		while (str[i] && quote[0] != str[i])
			i++;
	}
	return (0);
}

t_tokens	*expention_wildcard_case(char *to_handle)
{
	t_tokens	*tokens;

	if (is_wildcard(to_handle))
		return (wildcard(to_handle));
	create_tokens(&tokens, ft_strdup(to_handle));
	return (tokens);
}

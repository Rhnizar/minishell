/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:13:41 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/17 13:18:22 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	parentheses_number(char *str, int *count_paren)
{
	int	i;

	i = 0;
	while (str[i] && is_quote(str[i]) == 0)
	{
		if (str[i] == '(')
			(*count_paren)++;
		else if (str[i] == ')')
			(*count_paren)--;
		i++;
	}
	return (i);
}

void	check_parentheses(char *str)
{
	int		i;
	int		quote;
	int		count_paren;

	i = -1;
	count_paren = 0;
	quote = 0;
	while (str[++i])
	{
		i += parentheses_number(&str[i], &count_paren);
		quote = is_quote(str[i]);
		if (str[i + 1] == '\0' && quote > 0)
			return ;
		else if (str[i + 1] != '\0')
			i++;
		while (str[i] && quote != is_quote(str[i]))
			i++;
		if (str[i] == '\0' && quote != is_quote(str[i]))
			return ;
	}
	if (count_paren > 0)
		syntx_error("(");
	else if (count_paren < 0)
		syntx_error(")");
}

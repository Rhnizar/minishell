/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:09:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/19 12:56:41 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quote(t_check *check, int *i)
{
	if (check->str[*i] == '"' && check->sq == 0 && check->dq == 0)
		dq_sq(check, i, &check->dq);
	else if (check->str[*i] == '\'' && check->sq == 0 && check->dq == 0)
		dq_sq(check, i, &check->sq);
	else if (check->str[*i] == '"' && check->sq == 0 && check->dq == 1)
	{
		check->dq = 0;
		check->ot = join_to_str(check->ot, check->str[*i]);
	}
	else if (check->str[*i] == '\'' && check->sq == 1 && check->dq == 0)
	{
		check->sq = 0;
		check->ot = join_to_str(check->ot, check->str[*i]);
	}
	else
		check->ot = join_to_str(check->ot, check->str[*i]);
}

void	check_space_tab(t_check *check, int *i)
{
	check->ot = join_to_str(check->ot, '\x07');
	while (check->str[*i] && (check->str[*i] == ' ' || check->str[*i] == '\t'))
			check->ot = join_to_str(check->ot, check->str[(*i)++]);
	check->ot = join_to_str(check->ot, '\x07');
	if (check->str[*i] != '"' && check->str[*i] != '\'' \
		&& str_in_string(&check->str[*i]) == -1 \
		&& check_par(&check->str[*i]) == 0)
		check->ot = join_to_str(check->ot, check->str[*i]);
	else
		(*i)--;
}

int	check_par(char *str)
{
	int	i;
	int	count;
	int	count2;

	i = 0;
	count = 0;
	count2 = 0;
	while (str[i])
	{
		if (str_in_string(&str[i]) != -1 && count == count2)
			break ;
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count2++;
		i++;
	}
	return (count);
}

int	check2_par(char c, int *count)
{
	if (c == ')')
		(*count)--;
	if (*count == 0)
		return (1);
	else
		return (0);
}

char	**globa_split(t_check *check, char *output)
{
	char	**split;

	init_check(check, output);
	fill_with_nonpr_char(check);
	split = ft_split(check->ot, '\x07');
	free(check->ot);
	return (split);
}

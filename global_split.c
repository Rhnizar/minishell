/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:09:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/16 12:13:26 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotee(t_check **check, int *i)
{
	if ((*check)->str[*i] == '"' && (*check)->sq == 0 && (*check)->dq == 0)
		dq_sq(check, i, &(*check)->dq);
	else if ((*check)->str[*i] == '\'' \
		&& (*check)->sq == 0 && (*check)->dq == 0)
		dq_sq(check, i, &(*check)->sq);
	else if ((*check)->str[*i] == '"' && (*check)->sq == 0 && (*check)->dq == 1)
	{
		(*check)->dq = 0;
		join_str(check, *i);
	}
	else if ((*check)->str[*i] == '\'' \
		&& (*check)->sq == 1 && (*check)->dq == 0)
	{
		(*check)->sq = 0;
		join_str(check, *i);
	}
	else if ((*check)->sid != -1 && (*check)->sq == 0 && (*check)->dq == 0)
	{
		(*check)->ot = join_to_str((*check)->ot, '\x07');
		(*check)->ot = ft_strjoin((*check)->ot, (*check)->split[(*check)->sid]);
		(*check)->ot = join_to_str((*check)->ot, '\x07');
		*i += ft_strlen((*check)->split[(*check)->sid]) - 1;
	}
}

void	check_space_tab(t_check **check, int *i)
{
	if ((*check)->sq == 0 && (*check)->dq == 0)
	{
		while ((*check)->str[*i] && ((*check)->str[*i] == ' ' \
			|| (*check)->str[*i] == '\t'))
				(*i)++;
		if ((*check)->str[*i - 1] == ' ')
			(*check)->ot = join_to_str((*check)->ot, '\x07');
		else
			(*check)->ot = join_to_str((*check)->ot, (*check)->str[*i - 1]);
		if ((*check)->str[*i] != '"' && (*check)->str[*i] != '\'' \
			&& str_in_string(&(*check)->str[*i]) == -1)
			(*check)->ot = join_to_str((*check)->ot, (*check)->str[*i]);
		else
			(*i)--;
	}
}

void	fill_with_nonpr_char(t_check *check)
{
	int	i;

	i = -1;
	while (check->str[++i])
	{
		check->sid = str_in_string(&check->str[i]);
		if (check->str[i] == '"' || check->str[i] == '\'' || check->sid != -1)
			check_quotee(&check, &i);
		else if (check->str[i] == ' ' || check->str[i] == '\t')
			check_space_tab(&check, &i);
		else
			join_str(&check, i);
	}
}

char	**globa_split(t_check *check, char *output)
{
	char	**split;

	init_check(check, output);
	fill_with_nonpr_char(check);
	split = ft_split(check->ot, '\x07');
	return (split);
}

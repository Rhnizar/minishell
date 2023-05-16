/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:09:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/16 10:19:24 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_str(t_check **check, int i)
{
	(*check)->output = join_to_str((*check)->output, (*check)->str[i]);
			if ((*check)->str[i + 1] && str_in_string(&(*check)->str[i + 1]) != -1 \
				&& (*check)->dq == 0 && (*check)->sq ==0)
				(*check)->output = join_to_str((*check)->output, '\x07');
}

void	dq_sq(t_check **check, int *i, int *dq_or_sq)
{
	(*check)->output = join_to_str((*check)->output, (*check)->str[*i]);
	*dq_or_sq = 1;
}

void	check_quotee(t_check **check, int *i)
{
	if ((*check)->str[*i] && (*check)->str[*i] == '"' && (*check)->sq == 0 && (*check)->dq == 0)
		dq_sq(check, i, &(*check)->dq);
	else if ((*check)->str[*i] && (*check)->str[*i] == '\'' && (*check)->sq == 0 && (*check)->dq == 0)
		dq_sq(check, i, &(*check)->sq);
	else if ((*check)->str[*i] && (*check)->str[*i] == '"' && (*check)->sq == 0 && (*check)->dq == 1)
	{
		(*check)->dq = 0;
		join_str(check, *i);
	}
	else if ((*check)->str[*i] && (*check)->str[*i] == '\'' && (*check)->sq == 1 && (*check)->dq == 0)
	{
		(*check)->sq = 0;
		join_str(check, *i);
	}
	else if ((*check)->str[*i] && (*check)->sp_id != -1 && (*check)->sq == 0 && (*check)->dq == 0)
	{
		(*check)->output = ft_strjoin((*check)->output, (*check)->split[(*check)->sp_id]);
		*i += ft_strlen((*check)->split[(*check)->sp_id]) - 1;
		(*check)->output = join_to_str((*check)->output, '\x07');
	}
}

void	fill_with_nonpr_char(t_check *check)
{
	int	i;

	i = -1;
	while (check->str[++i])
	{
		check->sp_id = str_in_string(&check->str[i]);
		if (check->str[i] == '"' || check->str[i] == '\'' || check->sp_id != -1)
			check_quotee(&check, &i);
		else if (check->str[i] && check->str[i] == '\t' && check->sq == 0 && check->dq == 0)
			check->output = join_to_str(check->output, check->str[i]);
		else if (check->str[i] && check->str[i] == ' ' && check->sq == 0 && check->dq == 0)
		{
			while (check->str[i] && check->str[i] == ' ')
				i++;
			check->output = join_to_str(check->output, '\x07');
			if (check->str[i] != '"' && check->str[i] != '\'')
				check->output = join_to_str(check->output, check->str[i]);
			else
				i--;
		}
		else
			join_str(&check, i);
	}
}

char	**globa_split(t_check *check, char *output)
{
	char	**split;
	
	init_check(check, output);
	fill_with_nonpr_char(check);
	split = ft_split(check->output, '\x07');
	return (split);
}
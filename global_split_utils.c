/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:10:53 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/16 12:03:10 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_check(t_check	*check, char *read_line)
{
	char	*output;
	char	**split;

	output = NULL;
	split = ft_split(">> << || && > < |", ' ');
	check->str = read_line;
	check->ot = output;
	check->split = split;
	check->dq = 0;
	check->sq = 0;
	check->sid = 0;
}

int	find_separator(char **sep, char *str)
{
	int		sp_id;
	int		j;
	char	*output;

	j = 0;
	output = NULL;
	sp_id = -1;
	while (sep[j])
	{
		output = ft_strnstr(str, sep[j], ft_strlen(sep[j]));
		if (output != NULL)
			break ;
		j++;
	}
	if (output)
		sp_id = j;
	return (sp_id);
}

int	str_in_string(char *str)
{
	int		i;
	int		sp_id;
	char	**sp;

	i = 0;
	sp = ft_split(">> << || && > < |", ' ');
	sp_id = find_separator(sp, &str[i]);
	free_double_ptr(sp);
	return (sp_id);
}

void	join_str(t_check **check, int i)
{
	(*check)->ot = join_to_str((*check)->ot, (*check)->str[i]);
	if ((*check)->str[i + 1])
	{
		if (str_in_string(&(*check)->str[i + 1]) != -1)
		{
			if ((*check)->dq == 0 && (*check)->sq == 0)
				(*check)->ot = join_to_str((*check)->ot, '\x07');
		}
	}
}

void	dq_sq(t_check **check, int *i, int *dq_or_sq)
{
	(*check)->ot = join_to_str((*check)->ot, (*check)->str[*i]);
	*dq_or_sq = 1;
}

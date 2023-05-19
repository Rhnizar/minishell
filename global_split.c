/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:09:13 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/19 16:11:58 by rrhnizar         ###   ########.fr       */
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
		&& str_in_string(&check->str[*i]) == -1)
		check->ot = join_to_str(check->ot, check->str[*i]);
	else
		(*i)--;
}

void	fill_with_nonpr_char(t_check *check)
{
	int	i;

	i = -1;
	while (check->str[++i])
	{
		check->sid = str_in_string(&check->str[i]);
		if (check->str[i] == '"' || check->str[i] == '\'')
			check_quote(check, &i);
		else if (check->sid != -1 && check->sq == 0 && check->dq == 0)
		{
			check->ot = join_to_str(check->ot, '\x07');
			check->ot = ft_strjoin(check->ot, check->split[check->sid]);
			check->ot = join_to_str(check->ot, '\x07');
			i += ft_strlen(check->split[check->sid]) - 1;
		}
		else if ((check->str[i] == ' ' || check->str[i] == '\t') \
			&& (check->sq == 0 && check->dq == 0))
			check_space_tab(check, &i);
		else
			check->ot = join_to_str(check->ot, check->str[i]);
	}
	free_double_ptr(check->split);
}

t_tokens	*split_and_fill_list(char *output)
{
	char		**split;
	int			i;
	t_tokens	*lst;
	t_check		*check;

	lst = NULL;
	i = 0;
	check = malloc(sizeof(t_check));
	init_check(check, output);
	fill_with_nonpr_char(check);
	split = ft_split(check->ot, '\x07');
	free(check->ot);
	free(check);
	while (split[i])
		create_tokens(&lst, ft_strdup(split[i++]), 0);
	free_double_ptr(split);
	return (lst);
}

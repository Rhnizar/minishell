/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:09:52 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/18 10:36:41 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parenthesis(t_check *check, int *par, int *i)
{
	check->ot = join_to_str(check->ot, '\x07');
	while (check->str[*i] && check2_par(check->str[*i], par) == 0)
		check->ot = join_to_str(check->ot, check->str[(*i)++]);
	check->ot = join_to_str(check->ot, check->str[*i]);
	check->ot = join_to_str(check->ot, '\x07');
}

void	ft_call(t_check *check, int *i)
{
	int	par;

	par = 0;
	if (check->str[*i] == '(')
		par = check_par(&check->str[*i]);
	check->sid = str_in_string(&check->str[*i]);
	if (check->str[*i] == '"' || check->str[*i] == '\'')
		check_quote(check, i);
	else if (par != 0 && check->sq == 0 && check->dq == 0)
		parenthesis(check, &par, i);
	else if (check->sid != -1 && check->sq == 0 && check->dq == 0)
	{
		check->ot = join_to_str(check->ot, '\x07');
		check->ot = ft_strjoin(check->ot, check->split[check->sid]);
		check->ot = join_to_str(check->ot, '\x07');
		*i += ft_strlen(check->split[check->sid]) - 1;
	}
	else if ((check->str[*i] == ' ' || check->str[*i] == '\t') \
		&& (check->sq == 0 && check->dq == 0))
		check_space_tab(check, i);
	else
		check->ot = join_to_str(check->ot, check->str[*i]);
}

void	fill_with_nonpr_char(t_check *check)
{
	int	i;

	i = -1;
	while (check->str[++i])
		ft_call(check, &i);
	free_double_ptr(check->split);
}

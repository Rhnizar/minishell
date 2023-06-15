/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:10:53 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/01 15:44:04 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	dq_sq(t_check *check, int *i, int *dq_or_sq)
{
	check->ot = join_to_str(check->ot, check->str[*i]);
	*dq_or_sq = 1;
}

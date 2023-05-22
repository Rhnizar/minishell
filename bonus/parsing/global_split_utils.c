/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:10:53 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/22 21:30:51 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_check(t_check	*check, char *read_line)
{
	char	*output;
	char	**split;

	output = ft_strdup("");
	split = ft_split(">> << > < |", ' ');
	// split = ft_split(">> << || && > < | ( )", ' ');
	if (read_line)
		check->str = read_line;
	else
		check->str = NULL;
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
	sp = ft_split(">> << > < |", ' ');
	// sp = ft_split(">> << || && > < | ( )", ' ');
	sp_id = find_separator(sp, &str[i]);
	free_double_ptr(sp);
	return (sp_id);
}

void	dq_sq(t_check *check, int *i, int *dq_or_sq)
{
	check->ot = join_to_str(check->ot, check->str[*i]);
	*dq_or_sq = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt_error_mandatory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:24:44 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/23 12:25:22 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_check(t_check	*check, char *read_line)
{
	check->split = ft_split(">> << > < |", ' ');
	if (!check->split)
		return (-1);
	check->str = read_line;
	check->ot = NULL;
	check->dq = 0;
	check->sq = 0;
	check->sid = 0;
	return (0);
}
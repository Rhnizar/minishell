/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_first_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:02:31 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/09 15:03:10 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_in_string(char c, char *ref)
{
	int		j;

	j = 0;
	while (ref[j])
	{
		if (c == ref[j])
			return (j);
		j++;
	}
	return (-1);
}

int	count_split(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (char_in_string(str[i], "&|<>()*") != -1)
			count++;
		i++;
	}
	return (count);
}

int	cheack_sp_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (char_in_string(str[i], "&|<>()*") == -1)
		return (1);
	else
		return (0);
}

int	len_first_split(char *str)
{
	int	len;

	len = count_split(str);
	if (cheack_sp_char(str) == 0)
	{
		if (char_in_string(str[0], "&|<>()*") != -1)
			return (len * 2);
		else
			return (len * 2 + 1);
	}
	else
		return (len * 2 + 1);
}

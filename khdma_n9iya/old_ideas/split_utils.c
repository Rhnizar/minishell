/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:05:42 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/13 20:06:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quote(char *str)
{
	int		i;
	int		r;

	i = 0;
	while (str[i])
	{
		r = char_in_string(str[i], "\"'");
		if (r != -1)
			return (r);
		i++;
	}
	return (-1);
}

int count_quote(char *str, int r)
{
	char	ref[] = "\"'";
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ref[r])
			count++;
		i++;
	}
	return (count);
}

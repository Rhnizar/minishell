/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 08:10:02 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/08 08:13:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int char_in_string(char *str)
{
	char	ref[7] = "|<>()*";
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (ref[j])
		{
			if (str[i] == ref[j])
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}

int main(void)
{
	printf("%d\n", char_in_string("hello"));
	return (0);
}
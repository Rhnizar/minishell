/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:51:57 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/03 15:56:50 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*option(char *line)
{
	int		i;
	int		tmp;
	int		j;
	int		len;
	char	*opt;

	i = 0;
	len = 0;
	j = 0;
	while (line[i] && line[i] != '-')
		i++;
	if (line[i] == '-')
	{
		tmp = i;
		
		while(line[i] && line[i++] != ' ')
		{
			// i++;
			len++;
		}
		opt = malloc(sizeof(char) * len + 1);
		if (!opt)
			return (NULL);
		while (j < len)
			opt[j++] = line[tmp++];
		opt[j] = '\0';
		return (opt);
	}
	return (NULL);
}


int main(void)
{
	printf("just test   %s\n", option("hello -r "));
	return (0);
}
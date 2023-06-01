/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:32:55 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/01 15:30:02 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s && s[count])
		count++;
	return (count);
}

char	*add_quotes(char *str)
{
	int 	len;
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 1;
	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 3));
	if (!new)
		return (NULL);
	new[0] = '"';
	while (str[i])
		new[j++] = str[i++];
	new[j++] = '"';
	new[j] = '\0';
	return (new);
}


int main()
{
	printf("%s\n", add_quotes("hello"));
	return (0);
}
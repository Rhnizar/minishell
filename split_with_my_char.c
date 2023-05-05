/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_my_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:56:34 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/05 15:57:57 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			i++;
			if (str[i] == c || str[i] == '\0')
				count++;
		}
	}
	return (count);
}

static char	*word(char *str, char c)
{
	int		i;
	int		count;
	int		j;
	char	*wostr;

	i = 0;
	count = 0;
	j = 0;
	while (str[i] && str[i] == c)
	i++;
	while (str[i] && str[i] != c)
	{
		count++;
		i++;
	}
	i = 0;
	wostr = malloc (sizeof(char ) * count +1);
	if (!wostr)
		return (NULL);
	while (str[i] && str[i] == c)
	i++;
	while (str[i] && str[i] != c)
		wostr[j++] = str[i++];
	wostr[j] = '\0';
	return (wostr);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	split = malloc (sizeof(char *) * (str_count((char *)str, c) + 1));
	if (!split)
		return (NULL);
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c && j < str_count((char *)str, c))
	{
		split[j] = word((char *)&str[i], c);
		while (str[i] && str[i] != c)
			i++;
		while (str[i] && str[i] == c)
			i++;
		j++;
	}
	split[j] = 0;
	return (split);
}

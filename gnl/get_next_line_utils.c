/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:46:06 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/30 10:50:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenn(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*p;
	size_t		lens1;
	size_t		lens2;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	lens1 = ft_strlenn(s1);
	lens2 = ft_strlenn(s2);
	p = malloc(sizeof(char) * ((lens1 + lens2) + 1));
	if (!p)
		return (NULL);
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	free(s1);
	return (p);
}

char	*ft_strchrrida(char *str, char c)
{
	int		i;
	int		count;
	char	*new;

	count = 0;
	i = 0;
	while (str[count] && str[count] != c)
		count++;
	if (!str[count] || (str[count] == c && str[count + 1] == '\0'))
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlenn(str) - count) + 1);
	if (!new)
		return (NULL);
	count += 1;
	while (str[count])
		new[i++] = str[count++];
	new[i] = '\0';
	return (new);
}

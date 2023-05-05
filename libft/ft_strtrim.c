/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:56:42 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/01/10 19:19:51 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	checkset(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	ft_start(char *s1, char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		while (s1[i] && checkset(set, s1[i]))
			i++;
		if (s1[i] && !checkset(set, s1[i]))
			break ;
	}
	return (i);
}

static	int	lenorigine(char *s1, char *set)
{
	int	len;
	int	start;

	start = ft_start (s1, set);
	len = ft_strlen (s1) -1;
	while (s1[len] && len > start)
	{
		while (s1[len] && checkset(set, s1[len]))
			len--;
		if (s1[len] && !checkset(set, s1[len]))
			break ;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		j;

	if (!s1 || !set)
		return (NULL);
	start = ft_start((char *)s1, (char *)set);
	end = lenorigine((char *)s1, (char *)set);
	j = 0;
	res = malloc(sizeof(char) * ((end +1) - (start)) + 1);
	if (!res)
		return (0);
	while (start <= end)
		res[j++] = s1[start++];
	res[j] = '\0';
	return (res);
}

// int main(void)
// {

// 	// printf("%d\n", lenorigine("    123  hello  ", " "));
// 	// printf("%d\n", Start("    123  hello  ", " "));
// 	//printf("%s\n", ft_strtrim("   xxxtripouille   xxx", " x"));
// 	printf("%s\n", ft_strtrim("   xxx   xxx", " x"));

// 	//printf("%zu", ft_strlen("  Hello  "));
// }
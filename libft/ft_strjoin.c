/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:13:37 by kchaouki          #+#    #+#             */
/*   Updated: 2022/10/07 09:29:37 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	char	*joined_str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	joined_str = (char *)malloc(s1_len + s2_len + 1);
	if (!joined_str)
		return (0);
	while (i < s1_len)
	{
		joined_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		joined_str[s1_len + i] = s2[i];
		i++;
	}
	joined_str[s1_len + i] = '\0';
	return (joined_str);
}

// int main()
// {
// 	char str1[] = "Hello my ";
// 	char str2[] = "name is karim";
// 	puts(ft_strjoin(str1,str2));
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:52:24 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/05 15:47:07 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str2[i] == '\0')
		return ((char *)str1);
	if (len == 0)
		return (0);
	while (str1[i] && i < len)
	{
		j = 0;
		while (str1[i + j] == str2[j] && i + j < len)
		{
			if (str2[j + 1] == '\0')
				return (((char *)&str1[i]));
			j++;
		}
		i++;
	}
	return (0);
}

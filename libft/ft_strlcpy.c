/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:10:36 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:13:05 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	count;

	count = ft_strlen(src);
	i = 0;
	if (!size)
		return (count);
	while (src[i] && i < size -1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (count);
}

// int main(void)
// {
//      char dst[100]= "hello";
// 	 const char src[100] = "Wordhgf";
// 	 int n = ft_strlcpy(dst, src, 4);
//      printf("%d\n", n);
// 	 puts(dst);
// }
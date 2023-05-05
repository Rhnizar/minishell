/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:46:28 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/16 21:04:54 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lendest;
	size_t	lensrc;
	size_t	lenf;

	i = 0;
	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (lendest >= dstsize)
		return (dstsize + lensrc);
	else
	{
		lenf = lendest + lensrc;
		while (src[i] && lendest < (dstsize -1))
			dst[lendest++] = src[i++];
		dst[lendest] = '\0';
	}
	return (lenf);
}
// int main(void)
// {
// 	char dst[100] = "hello";
// 	char src[] = "1337";
// 	printf("%lu\n", strlcat(dst, src, 0));
// 	puts(dst);
// }
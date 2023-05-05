/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:15:44 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/01/10 19:18:35 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		while (len--)
		((char *)dst)[len] = ((char *)src)[len];
	}
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}

// int main()
// {
//   char str[40] = "1337 is a school of 42";
//   // dst = cdef 
//   // src = abcdef
//   memmove(str + 5, str + 2, 7);  //ababaf
//   puts(str +5);
//   return (0);
// }
// 1337 is a school of 42
// memmove(str + 5, str + 2, 7);
// str +5 ==> dst = is a sc)hool of 42
// str +2 ==> src = 37 is a school of 42
// 7 src ==> 37 is a
// 7 dst ==> is a sc
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:59:28 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/17 15:21:46 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

// int main(void)
// {
// 	char str[] = "abcdef";
// 	//printf("%s", str +2);
// 	//char s[] = "rida";
// 	puts(ft_memcpy(str, str +2, 2));
// }

// signal(SIGSEGV, sigsegv);
// 	title("ft_memcpy\t: ")	
// 	char dest[100];
// 	memset(dest, 'A', 100);
// 	ft_memcpy(dest, "coucou", 0);
// 	/* 1 */ check(dest[0] == 'A'); showLeaks();
// 	char src[] = {0, 0};
// 	ft_memcpy(dest, src, 2);
// 	int i = 0;
// 	for (; i < 100 && dest[i] == 0; ++i)
// 		;
// 	/* 2 */ check(i == 2 && dest[2] == 'A'); showLeaks();
// 	write(1, "\n", 1);
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:08:37 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/17 15:21:39 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((char *)s)[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	//char s[] = {0, 1, 2, 3, 4, 5};
// 	char s[] = "Rida ";
// 	printf("%s", ft_memchr(s, 'i', 4));
// }

// int iTest = 1;
// int main(void)
// {
// 	signal(SIGSEGV, sigsegv);
// 	title("ft_memchr\t: ")	
// 	char s[] = {0, 1, 2 ,3 ,4 ,5};
// 	/* 1 */ check(ft_memchr(s, 0, 0) == NULL); showLeaks();
// 	/* 2 */ check(ft_memchr(s, 0, 1) == s); showLeaks();
// 	/* 3 */ check(ft_memchr(s, 2, 3) == s + 2); showLeaks();
// 	/* 4 */ check(ft_memchr(s, 6, 6) == NULL); showLeaks();
// 	/* 5 */ check(ft_memchr(s, 2 + 256, 3) == s + 2); showLeaks(); //Cast check
// 	write(1, "\n", 1);
// 	return (0);
// }
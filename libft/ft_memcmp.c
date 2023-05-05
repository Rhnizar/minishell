/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:09:45 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/01/10 19:18:49 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
// int main(void)
// {
// 	char s[] = {-128, 0, 127, 0};
// 	char sCpy[] = {-128, 0, 127, 0};
// 	char s2[] = {0, 0, 127, 0};
// 	char s3[] = {0, 0, 42, 0};
// 	printf("%d", ft_memcmp(s, s2, 1));

// 	// /* 1 */ check(!ft_memcmp(s, sCpy, 4)); showLeaks();
// 	// /* 2 */ check(!ft_memcmp(s, s2, 0)); showLeaks();
// 	// /* 3 */ check(ft_memcmp(s, s2, 1) > 0); showLeaks();
// 	// /* 4 */ check(ft_memcmp(s2, s, 1) < 0); showLeaks();
// 	// /* 5 */ check(ft_memcmp(s2, s3, 4) != 0); showLeaks();
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:26:56 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 11:38:10 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (len-- > 0)
		((char *)b)[i++] = c;
	return (b);
}

// int main(void)
// {
// 	char str[] = "Hello";
// 	ft_memset(str, 'A', 2);
// 	printf("%s", str);
// }
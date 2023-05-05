/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:03:34 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:20:29 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen(s);
	while (l >= 0)
	{
		if (s[l] == (char)c)
			return ((char *)&s[l]);
		l--;
	}
	return (NULL);
}
// int main(void)
// {
//    char a[] = "karim";
//    puts(ft_strrchr(a, 'r'));
// }
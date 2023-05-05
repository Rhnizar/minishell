/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:01:31 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/17 13:27:28 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;

	i = 0;
	if (start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	else if (len >= ft_strlen((char *)s))
		p = (char *)malloc(sizeof(char ) * ((ft_strlen(s) - start) + 1));
	else
		p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (start <= ft_strlen(s) && i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

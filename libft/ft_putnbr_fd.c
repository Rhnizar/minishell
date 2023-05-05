/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:45:41 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/05 15:48:14 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	c = n + '0';
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n >= 0 && n <= 9)
			write (fd, &c, 1);
		else if (n < 0)
		{
			write (fd, "-", 1);
			ft_putnbr_fd ((n * (-1)), fd);
		}
		else
		{
			ft_putnbr_fd ((n / 10), fd);
			ft_putnbr_fd ((n % 10), fd);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:24:07 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:45:04 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd (s, fd);
	write (fd, "\n", 1);
}

// #include <fcntl.h>

// int main(void)
// {
// 	int fd;
// 	fd = open("file", O_CREAT | O_APPEND | O_WRONLY  | O_EXCL,
//       S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	  ft_putendl_fd("Hello Rida", fd);
// 	printf("%d", fd);
// }
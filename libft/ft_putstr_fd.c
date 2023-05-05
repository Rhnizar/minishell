/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:38:18 by rrhnizar          #+#    #+#             */
/*   Updated: 2022/10/14 22:41:18 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

//  #include <fcntl.h>

//  int main(void)
//  {
// 	 int fd;
// 	 fd = open("file.doc", O_CREAT | O_APPEND | O_WRONLY  | O_EXCL,
//      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//      ft_putstr_fd("HelloWord", fd);
//  }

// int main(void)
// {
// 	int fd;
// 	char s[] = "Hello World";
// 	fd = open("file.doc", O_CREAT | O_APPEND | O_WRONLY  | O_EXCL,
//    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
//    ft_putstr_fd(s, fd);
// }
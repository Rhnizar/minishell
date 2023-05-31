/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:38:27 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/31 09:56:42 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*here doc using file*/

// int main()
// {
// 	int	fd1 = open("/tmp/.tmp", O_CREAT|O_RDWR, 0777);
// 	int fd2 = open("outfile", O_CREAT|O_RDWR|O_TRUNC, 0777);
// 	write_to_pipe(fd1, "eof");
// 	close(fd1);
// 	fd1 = open("/tmp/.tmp", O_CREAT|O_RDWR, 0777);
// 	dup2(fd1, STDIN_FILENO);
// 	close(fd1);

// 	dup2(fd2, STDOUT_FILENO);
// 	close(fd2);
// 	char *args[] = {"/bin/cat", "-e", NULL};
// 	unlink(".tmp");
// 	execve("/bin/cat", args, NULL);
// 	return (0);
// }
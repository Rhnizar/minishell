/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:44:18 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/10 10:21:34 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

// int main() {
//     char *argv[] = { "/bin/ls", "-l", NULL };
//     char *envp[] = { NULL };

//     if (fork() == 0) {
//         // Child process
//         execve(argv[0], argv, envp);
//         // execve will only return if an error occurs
//         perror("execve");
//         return 1;
//     }

//     // Parent process
//     printf("Parent process continuing...\n");

//     return 0;
// }

int main(int argc, char **argv, char **env, char **arg4)
{
	(void)argc;
	(void)argv;
	(void)env;
	(void)arg4;
	int	i = 0;
	while (arg4[i])
		printf("%s\n", arg4[i++]);
	return (0);
}
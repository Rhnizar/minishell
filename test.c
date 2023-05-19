# include "minishell.h"

int main()
{
	// pid_t  pid;

	// int i = 0;
	// while (++i < 4)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		printf("child\n");
	// 		// while (1);
	// 	}
	// 		// break ;
	// }
	// if (pid == 0)
	// {
	// 	while (1);
	// }
	// waitpid(-1, NULL, 0);
	// char **str = ft_calloc(3, sizeof(char *));

	// printf("%s\n", str[0]);
	// printf("%s\n", str[1]);
	// printf("%s\n", str[2]);


	char *arg[] = {"", "ls", NULL};
	int fd = open("Makefile", O_RDONLY);

	dup2(fd, 0);

	dup2();
	execve("/bin/cat", arg, NULL);

	return (0);
}
// if (str[i] == '(')
// 	is_parenthesise = 1;

// if (is_parenthesise && str[i] = ')')
// 	is_parenthesise = 0;
// ("ls -la") && pwd

// (ls -la && (ls -la))

# include "minishell.h"

int main()
{
	pid_t  pid;

	int i = 0;
	while (++i < 4)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("child\n");
			// while (1);
		}
			// break ;
	}
	if (pid == 0)
	{
		while (1);
	}
	waitpid(-1, NULL, 0);
}
if (str[i] == '(')
	is_parenthesise = 1;

if (is_parenthesise && str[i] = ')')
	is_parenthesise = 0;
("ls -la") && pwd

(ls -la && (ls -la))
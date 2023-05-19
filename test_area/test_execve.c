#include "../minishell.h"


int main()
{
	char *arg[] = {"ls", "(ls -la)", NULL};

	execve("/bin/ls", arg, NULL);
	return (0);
}
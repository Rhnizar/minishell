#include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <signal.h>

int glob = 0;
void	sig_handl(int sig)
{
	if (sig == SIGINT)
	{
		glob = 1;
		printf("here\n");
	}
}

int main(void)
{
	int	i = 0;
	signal(SIGINT, sig_handl);
	while(1)
	{
		if (glob == 1)
			break ;
		printf("i = %d\n", i++);
	}
	return (0);
}



#include "minishell.h"

int	check_par(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(')
			count++;
		i++;
	}
	return(count);
}

int	check2_par(char *str)
{
	int count;
	int	i;

	i = 0;
	count = check_par(str);
	while(str[i])
	{
		if (str[i] == ')')
			count--;
		if (count == 0)
			return(1);
		i++;
	}
	return(0);
}
int main()
{
	printf("%d\n", check_par("(ls -la (jifj(jdigj)test1)test2)test3"));
	printf("%d\n", check2_par("(ls -la (jifj(jdigj)test1)test2)test3"));
	return (0);
}
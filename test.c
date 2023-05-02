/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/02 15:40:06 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <unistd.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// int main()
// {

// 	char *read_line = readline("minishell > ");
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	// printf("test\n");
	char *read_line;
	while (1)
	{
    	read_line = readline("minishell > ");
		add_history(read_line);
	}
    // write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	return 0;
}
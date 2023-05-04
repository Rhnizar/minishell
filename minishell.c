/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/04 16:24:14 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	(void) envp;
	char *read_line;
	char *ret_quote;
	while (1)
	{
    	read_line = readline("minishell> ");
		// print_error(ECNF, "test", 0);
		ret_quote = quotes_handler(read_line);
		printf("%s\n", ret_quote);
		free (ret_quote);
		
		add_history(read_line);
	}
	return 0;
}
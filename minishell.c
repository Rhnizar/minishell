/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/13 10:52:40 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *read_line;
	char *quote;
	// int	exit_status;
	while (1)
	{
    	read_line = readline("minishell> ");
		quote = quotes_handler(read_line);
		// exit_status = snytx_error_checker(read_line);
		add_history(read_line);
		// printf("%d\n", exit_status);
		printf("%s\n", quote);
		free(read_line);
	}
	return 0;
}
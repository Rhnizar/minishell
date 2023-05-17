/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/17 16:51:48 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *read_line;
	// char *quote;
	int	exit_status;
	int	i = 0;
	while (1)
	{
    	read_line = readline("minishell> ");
		// quote = quotes_handler(read_line);
		if (read_line)
			exit_status = syntax_error_handler(read_line);
		add_history(read_line);
		printf("%d\n", exit_status);
		free(read_line);
		i++;
	}
	return 0;
}
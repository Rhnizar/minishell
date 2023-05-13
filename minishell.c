/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/12 19:16:37 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *read_line;
	char *quote;
	while (1)
	{
    	read_line = readline("minishell> ");
		quote = quotes_handler(read_line);
		printf("%s\n", quote);
		add_history(read_line);
	}
	return 0;
}
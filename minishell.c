/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchaouki <kchaouki@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:40:05 by kchaouki          #+#    #+#             */
/*   Updated: 2023/05/08 09:01:37 by kchaouki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	(void) envp;


	// char *read_line;
	// char *ret_quote;
	// while (1)
	// {
	// 	env = create_env(envp);
    // 	read_line = readline("minishell> ");
		
	// 	print_env(env);
	// 	printf("--------------------\n");
	// 	int i = -1;
	// 	char	**envdptr = env_to_double_ptr(env); 
	// 	while (envdptr && envdptr[++i])
	// 		printf("%s\n", envdptr[i]);
	// 	// printf("%d\n", count_env_variables(env));
		
	// 	// print_error(ECNF, "test", 0);
	// 	// ret_quote = quotes_handler(read_line);
	// 	// printf("%s\n", ret_quote);
	// 	// free (ret_quote);
		
	// 	add_history(read_line);
	// }
	

	// print_env(env);
	// printf("--------------------\n");
	// int i = -1;
	// char	**envdptr = env_to_double_ptr(env); 
	// while (envdptr && envdptr[++i])
	// 	printf("%s\n", envdptr[i]);
	// free_env(env);
	// free_double_ptr(envdptr);
	return 0;
}
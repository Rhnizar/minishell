/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/13 12:37:24 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(void)
// {
// 	char	*read_line;
// 	t_cmdshell	*lst;

// 	lst = malloc(sizeof(t_cmdshell));
// 	while (1)
// 	{
// 		read_line = readline("minishell ~ "); 
// 		if (read_line[0] != 0)
// 			add_history(read_line);
// 	}
// 	return (0);
// }

// int main(int argc, char **argv)
// {
// 	char **split;
// 	int	i;

// 	i = 0;
// 	if (argc == 2)
// 	{
// 		split = my_split(argv[1]);
// 		while (split[i])
// 			printf("%s\n", split[i++]);
// 	}
// 	return (0);
// }
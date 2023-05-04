/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/04 11:24:52 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*read_line;
	t_cmdshell	*lst;

	lst = malloc(sizeof(t_cmdshell));
	while (1)
	{
		read_line = readline("minishell ~ "); 
		if (read_line[0] != 0)
			add_history(read_line);
		ft_putstr_fd("test", 2);
		// lst->cmd = command(read_line);
		// lst->opt = option(read_line);
		// lst->arg = argument(read_line);
		// print_list(lst);
	}
	return (0);
}
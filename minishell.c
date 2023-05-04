/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/04 07:33:23 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*read_line;
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	while (1)
	{
		read_line = readline("minishell ~ "); 
		if (read_line[0] != 0)
			add_history(read_line);
		lst->cmd = command(read_line);
		lst->opt = option(read_line);
		lst->arg = argument(read_line);
		print_list(lst);
	}
	return (0);
}
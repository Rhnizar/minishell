/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:20:11 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/05/16 10:23:19 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*read_line;
	char	**split;
	
	int		i;
	t_check	*check;
	check = malloc(sizeof(t_check));
	while (1)
	{
		read_line = readline("minishell ~ ");
		if (read_line[0] != 0)
			add_history(read_line);
		split = globa_split(check, read_line);
		i = 0;
		while (split[i])
		{
			printf("%s\n", split[i]);
			i++;
		}
		free_double_ptr(split);
	}
	return (0);
}

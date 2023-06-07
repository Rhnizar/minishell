/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:07:25 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/07 18:40:09 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_opt(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(t_args *args)
{
	t_args	*tmp_args;
	int		r;

	r = 0;
	if (args)
	{
		if (args->next)
		{
			tmp_args = args->next;
			while (tmp_args)
			{
				if (check_opt(args->str) == 1)
				{
					r = 1;
					tmp_args = tmp_args->next;
					continue ;
				}
				printf("%s ", tmp_args->str);
				tmp_args = tmp_args->next;
			}
			if (r == 0)
				printf("\n");
		}
		else
			printf("\n");
	}
}

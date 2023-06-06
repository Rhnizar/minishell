/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:03:23 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/06 12:13:21 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	exitt(t_args *args)
{
	printf("exit\n");
	if (!args->next)
		exit(0);
	if (args->next)
	{
		if (args->next->next && check_arg(args->next->str) == 0)
		{
			printf("bash: exit: too many arguments\n");
			exit(1);
		}
		if (check_arg(args->next->str) == 1 \
			|| ft_atoi(args->next->str) > LONG_MAX)
		{
			printf("bash: exit: %s: numeric argument required\n", \
				args->next->str);
			exit(255);
		}
		else
			exit(ft_atoi(args->next->str));
	}
}

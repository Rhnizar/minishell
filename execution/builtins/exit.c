/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhnizar <rrhnizar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:03:23 by rrhnizar          #+#    #+#             */
/*   Updated: 2023/06/07 15:14:06 by rrhnizar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static long	my_ft_atoi(char *str)
{
	int					sign;
	unsigned long		ret;
	int					i;

	ret = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		ret = ret * 10 + str[i++] - '0';
		if ((sign == -1 && ret - 1 > LONG_MAX) || (ret > LONG_MAX && sign == 1))
		{
			// printf("bash: exit: %s: numeric argument required\n", str);
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
	}
	return (ret * sign);
}

int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1 || (str[i] == '-' && i != 0) \
			|| (str[i] == '+' && i != 0))
			return (1);
		i++;
	}
	return (0);
}

void	exitt(t_args *args)
{
	if (args)
	{
		printf("exit\n");
		if (!args->next)
			exit(0);
		if (args->next->next && check_arg(args->next->str) == 0)
		{
			printf("bash: exit: too many arguments\n");
			exit(1);
		}
		if (check_arg(args->next->str) == 1)
		{
			printf("bash: exit: %s: numeric argument required\n", args->next->str);
			exit(255);
		}
		else
			exit(my_ft_atoi(args->next->str));
	}
}
